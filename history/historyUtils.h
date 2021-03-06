#ifndef HISTORYUTILS_H
#define HISTORYUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/myUtils.h"
#include "../utils/lauraUtils.h"
#include "../linkedlist/linkedList.h"
#include "../linkedlist/genericData.h"
#include "history.h"

LinkedList * HISTORY;
int HISTCOUNT;
int HISTFILECOUNT;
int HISTMAX;

void cleanHistoryList();
void buildHistoryList();
void trimList();
void addToHistory(char * s);
char * getFromHistory(int i);

#endif
