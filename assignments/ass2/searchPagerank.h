// Created by Aniket Chavan (z5265106) on 26/07/19
#ifndef SEARCHPAGERANK_H
#define SEARCHPAGERANK_H

typedef struct _matchedListNode {
    char *urlname;
    int numFound;
    double PR;
    struct _matchedListNode *next;
} matchedListNode;

typedef matchedListNode *matchedList;

typedef struct _listRep {
    matchedList first;
    matchedList curr;
    matchedList last;
    int nitems;
} ListRep;

typedef ListRep *List;

List newList();

matchedList newMatchedList(char *urlname);

matchedList newCompletedMatchedList(char *urlname, int numFound);

List findMatchedUrls(char *filename, char *queryWords[], int args);

void findPagerank(char *filename, List L);

void listAppend(List L, char *urlname);

void orderedListAppend(List L, char *urlname, int numFound);

void printList(List L);

void dropList(List L);

#endif
