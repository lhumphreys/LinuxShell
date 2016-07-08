#include "makeArgs.h"

void clean(int argc, char **argv)
{
	for(int i = 0; i < argc; i ++)
	{
		free(argv[i]);
	}

	free(argv);
}// end clean

void printargs(int argc, char **argv)
{
	int x;
	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);

}// end printargs

int makeargs(char *s, char *** argv)
{

	int t = -1;
	if(s != NULL)
	{
		int max = strlen(s);
		char scopy[max];
		strcpy(scopy, s);

		char * token;
		char * save;
		char * save2;

		token = strtok_r(scopy, " ", &save);
		t = 0;
		while(token != NULL){
			token = strtok_r(NULL, " ", &save);
			t++;
		}

		(*argv) = (char **)calloc(t + 1, sizeof(char*));

		int i = 0;
		token = strtok_r(s, " ", &save2);
		while(token != NULL){
			(*argv)[i] = (char*)calloc(strlen(token) + 1, sizeof(char));
			strcpy((*argv)[i], token);
			token = strtok_r(NULL, " ", &save2);
			i++;
		}

		(*argv)[t] = NULL;
	}

   return t;

}// end makeArgs










