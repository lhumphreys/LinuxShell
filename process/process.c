#include "process.h"
#include <unistd.h>
#include <stdlib.h>
#include "../path/pathUtils.h"


void forkIt(char ** argv)
{
	int status;
	pid_t pid = fork();

	if(pid != 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		execWithPath(argv);
	}

}

void forkToBackground(char ** argv)
{
	int status;
	pid_t pid = fork();
	
	//Parent just keeps on goin'
	//Scheduler takes over
	if(pid == 0)
	{
		execWithPath(argv);
	}
}

void execWithPath(char ** argv)
{
	Node * cur = (*PATH).head;
	Path * pdata;
	char p[255];
	//IT WORKS IT WORKS IT WORKS IT WORKS IT WORKS
	/**/
	while((*cur).next != NULL)
	{
		cur = (*cur).next;
		pdata = (Path*)(*cur).data;
		strncpy(p, (*pdata).location, 255);
		strncat(p, "/", 1);
		strncat(p, argv[0], (255 - strlen(p)));
		//printf("%s\n", p);
		int res = execv(p, argv);
		
	}
	printf("Command not found\n");
	exit(0);/**/
}

