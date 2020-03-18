// List.c ... implementation of simple List ADT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "List.h"

typedef struct Node *Link;

typedef struct Node {
	int  value;
	Link next;
} Node;

typedef struct ListRep {
	int  nnodes;
	Link first;
	Link last;
} ListRep;

// newList ... make new empty List
List newList()
{
	List new = malloc(sizeof(ListRep));
	assert(new != NULL);
	new->nnodes = 0;
	new->first = NULL;
	new->last = NULL;
	return new;
}

// ListShow ... display List as <a, b, c, d, ...z>
void ListShow(List L)
{
	assert(L != NULL);
	printf("[");
	Link curr = L->first;
	while (curr != NULL) {
		printf("%d",curr->value);
		if (curr->next != NULL) printf(", ");
		curr = curr->next;
	}
	printf("]\n");
}

// ListLength ... number of nodes in List
int ListLength(List L)
{
	assert(L != NULL);
	return (L->nnodes);
}

// ListAppend ... append a new value to List
void ListAppend(List L, int value)
{
	assert(L != NULL);
	Link new = malloc(sizeof(Node));
	assert(new != NULL);
	new->value = value;
	new->next = NULL;
	L->nnodes++;
	if (L->first == NULL)
		L->first = L->last = new;
	else {
		L->last->next = new;
		L->last = new;
	}
}


// ListReverse ... reverse a List
void ListReverse(List L)
{
	if (L == NULL || L->first == NULL || L->last == NULL) {
		printf("Invalid List\n");
		exit(1);
	}

	if (L->nnodes == 1)
		return;

	for (int i = 0; i < L->nnodes/2; i++) {
		Node *a = L->first;
		Node *b = L->first;

		// printf("Swapping %d with %d\n", i, L->nnodes-1-i);
		for (int j = 0; j < L->nnodes; j++) {
			if (j < i)
				a = a->next;
			if (j < L->nnodes - 1 - i){
				b = b->next;
			}
		}

		int tmp = b->value;
		b->value = a->value;
		a->value = tmp;
	}
}
