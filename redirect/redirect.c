#include "redirect.h"

int containsRedirect(char * s)
{
	int in;
	int out;
	int app;

	in = containsInputRedirect(s);
	out = containsOutputRedirect(s);
	app = containsAppendRedirect(s);

	if(in > 1 || out > 1 || app > 1)
	{
		return -1;
	}
	else if(out == 1 && app == 1)
	{
		return -1;
	}
	else if(in == 1 || out == 1 || app == 1)
	{
		return 1;
	}
	return 0;
}

int containsInputRedirect(char * s)
{
	char c;
	int tot = 0;
	int l = strlen(s);
	for(int i = 0; i < l; i++)
	{
		c = s[i];
		if(c == '<')
		{
			tot++;
		}
	}

	return tot;
}

int containsOutputRedirect(char * s)
{
	char c, n;
	int tot = 0;
	int l = strlen(s);
	for(int i = 0; i < l; i++)
	{
		c = s[i];
		if(c == '>')
		{	
			i++;
			n = s[i];
			if(n != '>')
			{
				tot++;
			}
			
		}
	}

	return tot;
}

int containsAppendRedirect(char * s)
{
	char c, n;
	int tot = 0;
	int l = strlen(s);
	for(int i = 0; i < l; i++)
	{
		c = s[i];
		if(c == '>')
		{
			n = s[i + 1];
			if(n == '>')
			{
				tot++;
			}
		}
	}

	return tot;
}

void parseRedirects(char * s, int * inFD, int * outFD, int * argc, char *** argv)
{
	int l = strlen(s);
	char command[l];
	char infile[l];
	char outfile[l];
	int inFlag = 0;
	int outFlag = 0;
	int appendFlag = 0;
	int none = -1;
	int k;
	char c;
	
	for(int i = 0; i < l; )
	{
		k = 0;
		c = s[i];

		if(c == NULL || c == ' ')
		{
			i++;
		}
		else if(c == '<')
		{	
			inFlag = 1;
			i++;
			c = s[i];
			if(c == ' ')
			{
				i++;
				c = s[i];
			}
			while(i < l && c != ' ' && c != '>')
			{
				infile[k] = c;
				i++;
				k++;
				c = s[i];
			}
			infile[k] = NULL;
		}
		else if(c == '>')
		{
			i++;
			c = s[i];
			if(c == '>')
			{
				appendFlag = 1;
				i++;
				c = s[i];
			}
			else
			{
				outFlag = 1;
			}
			if(c == ' ')
			{
				i++;
				c = s[i];
			}
			while(i < l && c != ' ' && c != '<')
			{
				outfile[k] = c;
				i++;
				k++;
				c = s[i];
			}
			outfile[k] = NULL;
		}
		else
		{	
			while(i < l && c != '<' && c != '>')
			{
				command[k] = c;
				i++;
				k++;
				c = s[i];
			}
			command[k] = NULL;
		}

		
	}

	

	int res = makeargs(command, argv);
	*argc = res;
	if(inFlag == 1)
	{
		int fd = open(infile, O_RDONLY);
		*inFD = fd;
	}
	else
	{
		*inFD = -1;
	}

	if(outFlag == 1)
	{
		int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		*outFD = fd;
	}
	else if(appendFlag == 1)
	{
		int fd = open(outfile, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
		*outFD = fd;
	}
	else
	{
		*outFD = -1;
	}
}

void redirectIt(char ** argv, int inFD, int outFD)
{
	int status;
	pid_t pid = fork();
	
	if(pid != 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		if(inFD != -1)
		{
			dup2(inFD, 0);
			close(inFD);
		}
		if(outFD != -1)
		{
			dup2(outFD, 1);
			close(outFD);
		}
		execWithPath(argv);
	}
}





