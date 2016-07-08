#include "listUtils.h"

Node * buildNode(FILE * fin, void *(*buildData)(FILE * in) ){

	Node * nn = (Node *)calloc(1, sizeof(Node));
	(*nn).data = buildData(fin);
	return nn;
}

Node * buildNode_Type(void * passedIn){
	Node * nn = (Node *)calloc(1, sizeof(Node));
	(*nn).data = passedIn;
	return nn;
}

void sort(LinkedList * theList, int (*compare)(const void *, const void *)){
	Node * cur = (*theList).head;
	Node * walker = (*cur).next;
	Node * smallest = (*cur).next;
	void * tmp;

	while((*cur).next != NULL)
	{
		cur = (*cur).next;
		walker = cur;
		smallest = cur;
		while((*walker).next != NULL)
		{
			walker = (*walker).next;
			if(compare((*walker).data, (*smallest).data) < 0)
			{
				smallest = walker;
			}
		}

		tmp = (*cur).data;
		(*cur).data = (*smallest).data;
		(*smallest).data = tmp;
	}
}

void buildList(LinkedList * myList, int total, FILE * fin, void * (*buildData)(FILE * in)){
	Node * prev = (*myList).head;
	Node * cur;
	for(int i = 0; i < total; i++)
	{
		cur = buildNode(fin, buildData);
		(*prev).next = cur;
		(*cur).prev = prev;
		prev = cur;
		(*myList).size++;
	}

}
