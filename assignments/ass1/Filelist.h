#include <stdio.h>
#include <stdlib.h>

#include "invertedIndex.h"

FileList newFileListNode(char *filename);

void FileListAppend(InvertedIndexBST tree, char *filename);

void printFileList(FileList L, FILE *fd);
