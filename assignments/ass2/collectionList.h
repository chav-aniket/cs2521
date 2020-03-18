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
void CollectionListAppend (CollectionList L, char *fileName, int ID);

char *returnFilename(CollectionList L);

void setCurrToFirst(CollectionList L);

void nextNode(CollectionList L);

void outlinkIncrement(CollectionList L);

void inlinkIncrement(CollectionList L, char *filename);

int currNull(CollectionList L);

int returnInlinkCount(CollectionList L, char *file);

int returnOutlinkCount(CollectionList L, char *file);

int returnNitems(CollectionList L);

int returnID(CollectionList L, char *url);

#endif
