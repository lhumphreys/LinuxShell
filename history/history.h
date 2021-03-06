#ifndef HISTORY_H
#define HISTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/myUtils.h"

struct history
{
	char * line;
};
typedef struct history History;

void printHistory(History * passedIn);
History * buildHistory(FILE * fin);
int compareHistory(const History * h1, const History * h2);
void cleanHistory(History * passedIn);
void printHistoryList();

#endif
