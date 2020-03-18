#include <assert.h>
// #include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <sysexits.h>

#include "collectionList.h"

typedef struct CollectionListNode {
	char *url;
	int ID;
	int inlink_count;
	int outlink_count;
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
	// if (new == NULL) err (EX_OSERR, "couldn't allocate CollectionList");
	new->curr = new->first = new->last = NULL;
	new->nitems = 0;
	return new;
}

static void freeCollectionListNode (CollectionListNode *node) {
	if (node == NULL) return;
	free(node->url);
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

static CollectionListNode *newCollectionListNode (char *str, int ID) {
	CollectionListNode *new = malloc (sizeof(*new));
	// if (new == NULL) err (EX_OSERR, "couldn't allocate CollectionList node");
	new->url = malloc(sizeof(char) * 101);
	strcpy(new->url, str);
	new->ID = ID;
	new->inlink_count = 0;
	new->outlink_count = 0;
	new->next = NULL;
	return new;
}

void CollectionListAppend (CollectionList L, char *fileName, int ID) {
	assert (L != NULL);
	CollectionListNode *new = newCollectionListNode(fileName, ID);

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
    return L->curr->url;
}

void setCurrToFirst(CollectionList L) {
    L->curr = L->first;
}

void nextNode(CollectionList L) {
    L->curr = L->curr->next;
}

// void outlinkIncrement(CollectionList L) {
// 	L->curr->outlink_count++;
// 	return;
// }

// void inlinkIncrement(CollectionList L, char *filename) {
// 	CollectionListNode *curr = L->first;
// 	while (curr != NULL) {
// 		if (strcmp(filename, curr->file) == 0) {
// 			curr->inlink_count++;
// 			return;
// 		}
// 		curr = curr->next;
// 	}
// }

// Returns 1 if curr node is NULL
int currNull(CollectionList L) {
	if (L->curr == NULL) {
		return 1;
	} else {
		return 0;
	}
	return 1;
}

// int returnInlinkCount(CollectionList L) {
// 	return L->curr->inlink_count;
// }

// int returnOutlinkCount(CollectionList L) {
// 	return L->curr->outlink_count;
// }

int returnNitems(CollectionList L) {
	return L->nitems;
}

int returnID(CollectionList L, char *url) {
	CollectionListNode *curr = L->first;
	while (curr != NULL) {
		if (strcmp(url, curr->url) == 0) {
			return curr->ID;
		}
		curr = curr->next;
	}
	return 0;
}