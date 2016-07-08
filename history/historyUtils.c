#include "historyUtils.h"

void cleanHistoryList()
{
	clearList(HISTORY, cleanHistory);
	free(HISTORY);
	HISTORY = NULL;
}

void buildHistoryList()
{
	HISTORY = linkedList();
	FILE * fin = fopen(".mysh_history", "r");
	if(fin != NULL)
	{
		
		int t = totalLinesInFile(fin);
		buildList(HISTORY, t, fin, buildHistory);
		fclose(fin);
	}

	trimList();
}

void trimList()
{

	if(HISTCOUNT > HISTFILECOUNT)
	{
		HISTMAX = HISTCOUNT;
	}
	else
	{
		HISTMAX = HISTFILECOUNT;
	}
	while((*HISTORY).size >= HISTMAX)
	{
		removeFirst(HISTORY, cleanHistory);
	}
}

void writeHistoryFile()
{
	FILE * fout = fopen(".mysh_history", "w");
	if(fout != NULL)
	{
		dup2(fileno(fout), 1);
		printList(HISTORY, printHistory);
		fclose(fout);
	}
	
}

void addToHistory(char * s)
{
	History * h = (History *)calloc(1, sizeof(History));

	int l = strlen(s);
	(*h).line = (char*)calloc(l + 1, sizeof(char));
	strncpy((*h).line, s, l);

	Node * nn = buildNode_Type(h);

	trimList();

	addLast(HISTORY, nn);
}

char * getFromHistory(int t)
{
	if(t > 0  && t <= (*HISTORY).size)
	{
		Node * cur = (*HISTORY).head;

		for(int i = 0; i < t; i ++)
		{
			cur = (*cur).next;
		}

		History * h = (History*)(*cur).data;
		return (*h).line;
	}
	
	return NULL;
}

void printHistoryList()
{
	int dif = (*HISTORY).size - HISTCOUNT;
	int i = 1;

	Node * cur = (*HISTORY).head;

	while(i <= dif)
	{
		cur = (*cur).next;
		i++;
	}

	while((*cur).next != NULL)
	{
		cur = (*cur).next;
		printf("%d ", i);
		printHistory((*cur).data);
		i++;
	}
}

