#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Filelist.h"
#include "BSTree.h"

InvertedIndexBST newInvertedIndexBST(char *str, char *filename) {
	InvertedIndexBST new = malloc(sizeof(struct InvertedIndexNode));
	new->left = new->right = NULL;
	new->fileList = newFileListNode(filename);
	new->word = malloc(sizeof(char) * 101);
	strcpy(new->word, str);
	return new;
}

InvertedIndexBST BSTreeInsert(InvertedIndexBST t, char *str, char *filename) {
	if (t == NULL)
		return newInvertedIndexBST(str, filename);
	if (strcmp(str, t->word) < 0) {
		t->left = BSTreeInsert(t->left, str, filename);
	} else if (strcmp(str, t->word) > 0) {
		t->right = BSTreeInsert(t->right, str, filename);
	}
	return t;
}

InvertedIndexBST FindBSTree(InvertedIndexBST t, char *str) {
	if (t == NULL)
		return NULL;

	if (strcmp(str, t->word) < 0) {
		return FindBSTree(t->left, str);
	} else if (strcmp(str, t->word) > 0) {
		return FindBSTree(t->right, str);
	} else if (strcmp(str, t->word) == 0) {
		return t;
	}
	return NULL;
}

void divideByWordCount(InvertedIndexBST t, int word_count, char *filename) {
	if (t == NULL)
		return;
	divideByWordCount(t->left, word_count, filename);
	divideByWordCount(t->right, word_count, filename);
	FileList curr = t->fileList;
	while (curr != NULL) {
		if (strcmp(filename, curr->filename) == 0) {
			curr->tf = curr->tf/word_count;
		}
		curr = curr->next;
	}
	return;
}

InvertedIndexBST cloneInvertedIndexBST(InvertedIndexBST tree) {
	InvertedIndexBST new = malloc(sizeof(struct InvertedIndexNode));
	new->left = new->right = NULL;
	new->fileList = tree->fileList;
	new->word = malloc(sizeof(char) * 101);
	strcpy(new->word, tree->word);
	return new;
}
