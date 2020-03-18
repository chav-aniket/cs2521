#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "invertedIndex.h"

InvertedIndexBST newInvertedIndexBST();

InvertedIndexBST newInvertedIndexNode(char *str);

InvertedIndexBST BSTreeInsert(InvertedIndexBST t, char *str, char *filename);

InvertedIndexBST FindBSTree(InvertedIndexBST t, char *str);

void divideByWordCount(InvertedIndexBST t, int wordCount, char *filename);

InvertedIndexBST cloneInvertedIndexBST(InvertedIndexBST tree);
