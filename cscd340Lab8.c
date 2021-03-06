#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./utils/lauraUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./linkedlist/linkedList.h"
#include "./path/path.h"
#include "./path/pathUtils.h"
#include "./history/history.h"
#include "./history/historyUtils.h"


int main()
{

/* Stu's Code */
  int argc, pipeCount;
  char **argv = NULL, s[MAX];
  int preCount = 0, postCount = 0;
  char ** prePipe = NULL, ** postPipe = NULL;
//Laura's two lines
  char ** midPipe = NULL;
  int midCount = 0;
	int redirCount;
	char * h;
	int inFD;
	int outFD;

	FILE * rc = fopen(".myshrc", "r");
	if(rc != NULL)
	{
		while(!feof(rc))
		{
			fgets(s, MAX, rc);
			strip(s);
			if(strncmp(s, "PATH=", 5)==0)
			{
				replacePath(NULL);
				parsePath(s);
			}
			else if(strncmp(s, "HISTCOUNT=", 10)==0)
			{
				int i;
				sscanf(&(s[10]), "%d", &i);
				HISTCOUNT = i;
					
			}
			else if(strncmp(s, "HISTFILECOUNT=", 14)==0)
			{
				int i;
				sscanf(&(s[14]), "%d", &i);
				HISTFILECOUNT = i;
			}
		}
		
		fclose(rc);
	}
	else{
		char * p = getenv("PATH");
		replacePath(p);
		HISTCOUNT = 1000;
		HISTFILECOUNT = 2000;
	}
	
	buildHistoryList();

  printf("command?: ");
  fgets(s, MAX, stdin);
  strip(s);

  while(strcmp(s, "exit") != 0)
  { /* End Stu's Code */
	h = getFromHistory((*HISTORY).size);
	if(strncmp(s, "!", 1)==0)
	{
		if(strcmp(s, "!!")==0)
		{
			if(h != NULL)
			{
				strncpy(s, h, MAX);
				printf("%s\n", s);
			}
			else
			{
				printf("History empty.\n");
			}
		}
		else
		{
			int i;
			sscanf(&(s[1]), "%d", &i);
			h = getFromHistory(i);
			if(h!= NULL)
			{
				strncpy(s, h, MAX);
				printf("%s\n", s);
			}
			else{
				printf("Incorrect syntax.\n");
			}
		}
	}
	else
	{
		if(h == NULL || strcmp(s, h)!=0)
		{
 			addToHistory(s);
		}
	}

	pipeCount = containsPipe(s);
	redirCount = containsRedirect(s);
	if(strlen(s) == 0)
	{
		//do nothing
	}
	else if(strcmp(s, "history")==0)
	{	
		if((*HISTORY).size > 0)
		{
			printHistoryList();
		}
	}
	else if(strncmp(s, "PATH=", 5)==0)
	{
		parsePath(s);
	}
	else if(strncmp(s, "HISTCOUNT=", 10)==0)
	{
		int i;
		sscanf(&(s[10]), "%d", &i);
		HISTCOUNT = i;
	}
	else if(strncmp(s, "HISTFILECOUNT=", 14)==0)
	{
		int i;
		sscanf(&(s[14]), "%d", &i);
		HISTFILECOUNT = i;
	}
	else if(strncmp(s, "cd ", 3)==0)
	{
		char * p = &(s[3]);
		chdir(p);
	}
	else if(strstr(s, "&") != NULL)
	{
		int l = strlen(s);
		char c;

		for(int i = 0; i < l; i++)
		{
			c = s[i];
			if(c=='&')
			{
				s[i] = NULL;
			}
		}

		argc = makeargs(s, &argv);
	  	if(argc != -1)
			//printargs(argc, argv);
	  		forkToBackground(argv);
	  
	  	clean(argc, argv);
	  	argv = NULL;
	}
	else if(pipeCount > 0)
	{
		inFD = -1;
		outFD = -1;
		if(pipeCount == 1)
		{	
			prePipe = parsePrePipe(s, &preCount, &inFD);
			postPipe = parsePostPipe(s, &postCount, &outFD);
			pipeIt(prePipe, postPipe, inFD, outFD);
			clean(preCount, prePipe);
			clean(postCount, postPipe);
		}else{
			prePipe = parsePrePipe(s, &preCount, &inFD);
			midPipe = parseMidPipe(s, &midCount);
			postPipe = parsePostPipe(s, &postCount, &outFD);
			pipeItTwice(prePipe, midPipe, postPipe, inFD, outFD);
			clean(preCount, prePipe);
			clean(midCount, midPipe);
			clean(postCount, postPipe);
		}
	}
	else if(redirCount != 0)
	{
		if(redirCount == -1)
		{
			printf("Illegal number of redirects.\n");
		}
		else
		{	
			parseRedirects(s, &inFD, &outFD, &argc, &argv);
			redirectIt(argv, inFD, outFD);
			clean(argc, argv);
		}
	}
	else
	{
		argc = makeargs(s, &argv);
	  	if(argc != -1)
			//printargs(argc, argv);
	  		forkIt(argv);
	  
	  	clean(argc, argv);
	  	argv = NULL;
	}//End Laura's Code
	
/* Stu's Code */
	printf("command?: ");
	fgets(s, MAX, stdin);
      	strip(s);

  }// end while
/* End Stu's Code */  

	cleanPath();
	writeHistoryFile();
	cleanHistoryList();
  return 0;

}// end main



