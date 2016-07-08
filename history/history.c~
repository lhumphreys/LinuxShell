#include "history.h"

void printHistory(History * passedIn)
{
	printf("%s\n", (*passedIn).line);
}

History * buildHistory(FILE * fin)
{
	char buff[MAX];
	char * save;
	int l;

	History * h = (History *)calloc(1, sizeof(History));
	fgets(buff, MAX, fin);

	strtok_r(buff, " ", &save);

	l = strlen(save);
	(*h).line = (char *)calloc(l + 1, sizeof(char));
	strncpy((*h).line, save, l - 1);

	return h;
}

int compareHistory(const History * h1, const History * h2)
{
	int cmp = 0;
	cmp = strcmp((*h1).line, (*h2).line);
}

void cleanHistory(History * passedIn)
{
	free((*passedIn).line);
	(*passedIn).line = NULL;
	free(passedIn);
	passedIn = NULL;
}
