#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "invertedIndex.h"

TfIdfList newList(char *filename, double tfidf);

TfIdfList tfidfInsert(TfIdfList head, char *filename, double tfidf);

double tfidfCalc(int D, double Appearances, FileList node);

TfIdfList isTfIdfAdded(TfIdfList head, char *filename);

int isTfIdfUnique(TfIdfList head, double tfidf);

void freeTfIdfList(TfIdfList head);

TfIdfList orderList(TfIdfList head);
