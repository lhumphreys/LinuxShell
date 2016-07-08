#include "path.h"

void printType(Path * passedIn)
{
	printf("%s\n", (*passedIn).location);
}

void * buildType(FILE * fin)
{

	char buff[255];
	int l;

	Path * newPath = (Path *)calloc(1, sizeof(Path));

	fgets(buff, 255, fin);
	l = strlen(buff);
	(*newPath).location = (char*)calloc(l, sizeof(char));
	strncpy((*newPath).location, buff, l );

	return newPath;
}

void * buildType_Prompt(FILE * fin)
{
	//Not implemented
	return NULL;
}

int compare(const Path * p1, const Path * p2)
{
	int cmp = 0;
	cmp = strncmp((*p1).location, (*p2).location, 255);
	return cmp;
}

void cleanType(Path * passedIn)
{
	free((*passedIn).location);
	(*passedIn).location = NULL;
	free(passedIn);
	passedIn = NULL;
}





