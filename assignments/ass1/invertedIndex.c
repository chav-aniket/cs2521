#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "invertedIndex.h"
#include "CollectionList.h"
#include "BSTree.h"
#include "Filelist.h"
#include "tfidf.h"

void printInvertedIndexHelper(InvertedIndexBST tree, FILE *fd);

char *normaliseWord(char *str) {
	for (int i = 0; i < strlen(str); i++) {
		str[i] = tolower(str[i]);
	}
	if (isspace(str[0])) {
		memmove(&str[0], &str[1], strlen(str)-1);
	}
	if (isspace(str[strlen(str)-1])) {
		str[strlen(str)-1] = '\0';
	}
	if (str[strlen(str)-1] == '.' || str[strlen(str)-1] == ',' ||
		str[strlen(str)-1] == '?' || str[strlen(str)-1] == ';') {
		str[strlen(str)-1] = '\0';
	}
	return str;
}

InvertedIndexBST generateInvertedIndex(char *collectionFilename) {
	FILE *f;
	char filename[101];
	char word[101];
	char normalised[101];

	CollectionList collectionL = newCollectionList();
	f = fopen(collectionFilename, "r");

	while (fscanf(f, "%s", filename) == 1) {
		CollectionListAppend(collectionL, filename);
	}
	fclose(f);

	InvertedIndexBST t = NULL;
	InvertedIndexBST currBST = NULL;

	setCurrToFirst(collectionL);
	while (!currNull(collectionL)) {
		strcpy(filename, returnFilename(collectionL));
		f = fopen(filename, "r");
		while (fscanf(f, "%s", word) == 1) {
			strcpy(normalised, normaliseWord(word));
			currBST = FindBSTree(t, normalised);
			if (currBST == NULL) {
				t = BSTreeInsert(t, normalised, filename);
			} else {
				currBST = FindBSTree(t, normalised);
				FileListAppend(currBST, filename);
			}
			wordIncrement(collectionL);
		}
		divideByWordCount(t, returnWordCount(collectionL), filename);
		fclose(f);
		nextNode(collectionL);
	}
	freeCollectionList(collectionL);
	return t;
}

void printInvertedIndex(InvertedIndexBST tree) {
	FILE *fd;
	fd = fopen("invertedIndex.txt", "w");
	printInvertedIndexHelper(tree, fd);
	fclose(fd);
}

void printInvertedIndexHelper(InvertedIndexBST tree, FILE *fd) {
	if (tree == NULL)
		return;
	printInvertedIndexHelper(tree->left, fd);

	//printf("%s ", tree->word);
	fprintf(fd, "%s ", tree->word);


	printFileList(tree->fileList, fd);
	//printf("\n");
	fprintf(fd, "\n");

	printInvertedIndexHelper(tree->right, fd);
}

TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord , int D) {
	TfIdfList head = NULL;
	double Appearances = 0;
	InvertedIndexBST word = FindBSTree(tree, searchWord);

	FileList curr = word->fileList;
	while (curr != NULL) {
		Appearances++;
		curr = curr->next;
	}

	curr = word->fileList;
	while (curr != NULL) {
		if (head == NULL) {
			head = newList(curr->filename, tfidfCalc(D, Appearances, curr));
			/*printf("%s is %lf\n", curr->filename, tfidfCalc(D, Appearances, curr));*/
		} else {
			head = tfidfInsert(head, curr->filename, tfidfCalc(D, Appearances, curr));
			/*printf("%s is %lf\n", curr->filename, tfidfCalc(D, Appearances, curr));*/
		}
		curr = curr->next;
	}
	return head;
}

TfIdfList retrieve(InvertedIndexBST tree, char* searchWords[] , int D) {
	TfIdfList head = NULL;

	for (int i = 0; searchWords[i] != NULL; i++) {
		TfIdfList List = calculateTfIdf(tree, searchWords[i], D);
		TfIdfList curr = List;
		while (curr != NULL) {
			if (head == NULL) {
				head = tfidfInsert(head, curr->filename, curr->tfidf_sum);
			} else {
				TfIdfList tmp = isTfIdfAdded(head, curr->filename);
				if (tmp != NULL) {
					tmp->tfidf_sum += curr->tfidf_sum;
				} else {
					head = tfidfInsert(head, curr->filename, curr->tfidf_sum);
				}
			}
			curr = curr->next;
		}
		freeTfIdfList(List);
	}
	TfIdfList newHead = orderList(head);
	freeTfIdfList(head);
	return newHead;
}
