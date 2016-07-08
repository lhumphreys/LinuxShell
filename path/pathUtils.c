#include "pathUtils.h"


void parsePath(char * s)
{
	int max = strlen(s);
	char appSyntax[12];
	char repSyntax[6];
	strncpy(appSyntax, s, 11);
	strncpy(repSyntax, s, 5);
	appSyntax[11] = NULL;
	repSyntax[5] = NULL;

	char * p = NULL;

	if(strcmp(appSyntax, "PATH=$PATH:")==0)
	{
		p = &(s[11]);
		appendPath(p);
	}
	else if(strcmp(repSyntax, "PATH=")==0)
	{
		p = &(s[5]);
		replacePath(p);
	}
	else
	{
		printf("Incorrect syntax\n");
	}
	
	
}

void appendPath(char * str)
{
	int max = strlen(str);
	char scopy[max];
	strcpy(scopy, str);
	char * token;
	char * save;

	token = strtok_r(scopy, ":", &save);

	while(token != NULL)
	{
		Path * newPath = (Path *)calloc(1, sizeof(Path));
		int l = strlen(token);
		(*newPath).location = (char*)calloc(l + 1, sizeof(char));
		strncpy((*newPath).location, token, l);

		Node * nn = buildNode_Type(newPath);
		addLast(PATH, nn);

		token = strtok_r(NULL, ":", &save);
	}
}

void replacePath(char * str)
{
	if(PATH != NULL)
	{
		cleanPath();
	}

	PATH = linkedList();
	if(str != NULL)
	{
		appendPath(str);
	}
	
}

void cleanPath()
{
	clearList(PATH, cleanType);
	free(PATH);
	PATH=NULL;
}


