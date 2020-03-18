#ifndef COLLECTIONLIST_H
#define COLLECTIONLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct CollectionListRep *CollectionList;

/** Create a new, empty CollectionList. */
CollectionList newCollectionList (void);

/** Release all resources associated with a CollectionList. */
void freeCollectionList (CollectionList L);

/** Append a node to a CollectionList */
void CollectionListAppend (CollectionList L, char *fileName);

char *returnFilename(CollectionList L);

void setCurrToFirst(CollectionList L);

void nextNode(CollectionList L);

void wordIncrement(CollectionList L);

int currNull(CollectionList L);

int returnWordCount(CollectionList L);

#endif
