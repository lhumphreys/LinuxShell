#include "pipes.h"

int containsPipe(char *s)
{
	int max = strlen(s);
	char scopy[max];
	strcpy(scopy, s);
	int c = 0;
	char * token;
	char * save;

	token = strtok_r(scopy, "|", &save);
	c = 0;
	
	while(token != NULL)
	{
		token = strtok_r(NULL, "|", &save);
		c++;
	}

	c--;

	return c;
}

char ** parsePrePipe(char *s, int * preCount, int * inFD)
{
	int max = strlen(s);
	char scopy[max];
	strcpy(scopy, s);
	char * token;
	char * save;
	int res;
	int temp;

	token = strtok_r(scopy, "|", &save);
	char ** prePipe = NULL;

	if(containsInputRedirect(token) > 0)
	{	
		parseRedirects(token, inFD, &temp, &res, &prePipe);
	}
	else{
		res = makeargs(token, &prePipe);
	}

	*preCount = res;
	return prePipe;
}

char ** parsePostPipe(char *s, int * postCount, int * outFD)
{
	int l = strlen(s);
	char scopy[MAX];
	strcpy(scopy, s);
	char * lastToken;
	char * token;
	char * save;
	int res;
	int temp = 0;

	token = strtok_r(scopy, "|", &save);

	while(token != NULL){
		lastToken = token;
		token = strtok_r(NULL, "|", &save);
	}

	char ** postPipe = NULL;


	if(containsOutputRedirect(lastToken) > 0 || containsAppendRedirect(lastToken) > 0)
	{
		parseRedirects(lastToken, &temp, outFD, &res, &postPipe);
	}
	else
	{
		res = makeargs(lastToken, &postPipe);
		
	}	
	*postCount = res;

	

	return postPipe;
}

char ** parseMidPipe(char *s, int * midCount)
{
	int max = strlen(s);
	char scopy[max];
	strcpy(scopy, s);
	char * token;
	char * save;

	token = strtok_r(scopy, "|", &save);
	token = strtok_r(NULL, "|", &save);

	char ** midPipe = NULL;
	int res = makeargs(token, &midPipe);
	*midCount = res;

	return midPipe;
}

void pipeIt(char ** prePipe, char ** postPipe, int inFD, int outFD)
{
	int status;
	pid_t pid1 = fork();
	if(pid1 != 0)
	{
		waitpid(pid1, &status, 0);
	}
	else
	{
		int s2;
		int fd[2];
		int res = pipe(fd);
		pid_t pid = fork();
		if(pid != 0)
		{
			waitpid(pid, &s2, 0);
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);

			if(outFD != -1)
			{
				dup2(outFD, 1);
				close(outFD);
			}

			execWithPath(postPipe);
			exit(0);
		}
		else
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);

			if(inFD != -1)
			{
				dup2(inFD, 0);
				close(inFD);
			}

			execWithPath(prePipe);
			exit(0);
		}
	}
}

void pipeItTwice(char ** prePipe, char ** midPipe, char ** postPipe, int inFD, int outFD)
{
	int status;
	pid_t pid1 = fork();
	if(pid1 != 0)
	{
		waitpid(pid1, &status, 0);
	}
	else
	{	//First pipe 
		// If the command is 'ls | sort | wc -w'
		int fd[2];
		int res = pipe(fd);
		pid_t pid = fork();
		if(pid != 0) //Parent (wc -w)
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);

			if(outFD != -1)
			{
				dup2(outFD, 1);
				close(outFD);
			}

			execWithPath(postPipe);
			exit(0);
		}
		else
		{
			int fd2[2];
			int res2 = pipe(fd2);
			pid_t pid2 = fork();
			
			if(pid2 != 0)//Parent/child (sort)
			{	
				//set up first pipe
				close(fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
				//set up second pipe
				close(fd2[1]);
				dup2(fd2[0], 0);
				close(fd2[0]);
				execWithPath(midPipe);
				exit(0);
			}
			else//Child/child (ls)
			{
				close(fd2[0]);
				dup2(fd2[1], 1);
				close(fd2[1]);

				if(inFD != -1)
				{
					dup2(inFD, 0);
					close(inFD);
				}

				execWithPath(prePipe);
				exit(0);
			}			
		}
	}
}







