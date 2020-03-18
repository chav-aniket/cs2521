#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "CollectionList.h"

typedef struct CollectionListNode {
	char *file;
	double word_count;
	struct CollectionListNode *next;
} CollectionListNode;

typedef struct CollectionListRep {
	size_t nitems;
	CollectionListNode *first;
	CollectionListNode *curr;
	CollectionListNode *last;
} CollectionListRep;

CollectionList newCollectionList (void) {
	CollectionList new = malloc (sizeof(*new));
	if (new == NULL) err (EX_OSERR, "couldn't allocate CollectionList");
	new->curr = new->first = new->last = NULL;
	new->nitems = 0;
	return new;
}

static void freeCollectionListNode (CollectionListNode *node) {
	if (node == NULL) return;
	free(node->file);
	free(node);
}

void freeCollectionList (CollectionList L) {
	if (L == NULL) return;

	CollectionListNode *curr = L->first;
	while (curr != NULL) {
		CollectionListNode *next = curr->next;
		freeCollectionListNode(curr);
		curr = next;
	}
	free (L);
}

static CollectionListNode *newCollectionListNode (char *str) {
	CollectionListNode *new = malloc (sizeof(*new));
	if (new == NULL) err (EX_OSERR, "couldn't allocate CollectionList node");
	new->file = malloc(sizeof(char) * 101);
	strcpy(new->file, str);
	new->next = NULL;
	return new;
}

void CollectionListAppend (CollectionList L, char *fileName) {
	assert (L != NULL);
	CollectionListNode *new = newCollectionListNode(fileName);

	if (L->nitems == 0) {
		L->first = new;
	    L->curr = new;
	    L->last = new;
	} else {
		L->last->next = new;
		L->curr = new;
		L->last = new;
	}
	L->nitems++;
}

char *returnFilename(CollectionList L) {
    return L->curr->file;
}

void setCurrToFirst(CollectionList L) {
    L->curr = L->first;
}

void nextNode(CollectionList L) {
    L->curr = L->curr->next;
}

void wordIncrement(CollectionList L) {
	L->curr->word_count++;
	return;
}

int currNull(CollectionList L) {
	if (L->curr == NULL) {
		return 1;
	} else {
		return 0;
	}
	return 1;
}

int returnWordCount(CollectionList L) {
	return L->curr->word_count;
}
