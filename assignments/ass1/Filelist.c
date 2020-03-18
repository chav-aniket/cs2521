#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "invertedIndex.h"

FileList newFileListNode(char *filename) {
	FileList new = malloc(sizeof(*new));
	new->filename = malloc(sizeof(char) * 101);
	strcpy(new->filename, filename);
	new->tf = 1;
	new->next = NULL;
	return new;
}

void FileListAppend(InvertedIndexBST tree, char *filename) {
	if (strcmp(filename, tree->fileList->filename) < 0) {
		FileList new = newFileListNode(filename);
		new->next = tree->fileList;
		tree->fileList = new;
	} else {
		FileList curr = tree->fileList;
		FileList prev = NULL;
		while (curr != NULL && (strcmp(filename, curr->filename) == 0 ||
				strcmp(filename, curr->filename) > 0)) {
			prev = curr;
			curr = curr->next;
		}
		if (strcmp(filename, prev->filename) == 0) {
			prev->tf++;
		} else if (strcmp(filename, prev->filename) > 0) {
			FileList new = newFileListNode(filename);
			prev->next = new;
			new->next = curr;
		}
	}
}

void printFileList(FileList L, FILE *fd) {
	FileList curr = L;
	while (curr != NULL) {
		//printf("%s ", curr->filename);
		fprintf(fd, "%s ", curr->filename);
		curr = curr->next;
	}
	return;
}
