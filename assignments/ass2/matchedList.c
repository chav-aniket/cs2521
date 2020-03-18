// Created by Aniket Chavan (z5265106) on 26/07/19

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "searchPagerank.h"

List newList() {
    List new = malloc(sizeof *new);
    new->first = NULL;
    new->curr = NULL;
    new->last = NULL;
    new->nitems = 0;
    return new;
}

matchedList newMatchedList(char *urlname) {
    matchedList new = malloc (sizeof *new);
    new->urlname = malloc (sizeof(char)*100);
    strcpy(new->urlname, urlname);
    new->numFound = 1;
    new->PR = 0;
    new->next = NULL;
    return new;
}

matchedList newCompletedMatchedList(char *urlname, int numFound) {
    matchedList new = malloc (sizeof(new));
    new->urlname = malloc (sizeof(char)*100);
    strcpy(new->urlname, urlname);
    new->numFound = numFound;
    new->next = NULL;
    return new;
}

void listAppend(List L, char *urlname) {

    if (L->first == NULL) {
        matchedList new = newMatchedList(urlname);
        L->first = new;
        L->curr = new;
        L->last = new;
        return;
    }

    L->curr = L->first;
    int i = 0;
    while (L->curr != NULL) {
        if (strcmp(urlname, L->curr->urlname) == 0) {
            L->curr->numFound++;
            return;
        }
        i++;
        L->curr = L->curr->next;
    }

    matchedList new = newMatchedList(urlname);
    L->last->next = new;
    L->last = new;
    L->curr = new;
    L->nitems++;
}

void orderedListAppend(List L, char *urlname, int numFound) {

    matchedList new = newCompletedMatchedList(urlname, numFound);

    if (L->first == NULL) {
        L->first = new;
        L->curr = new;
        L->last = new;
        L->nitems++;
        return;
    }

    if (numFound > L->first->numFound) {
        new->next = L->first;
        L->first = new;
        L->curr = new;
    } else if (numFound <= L->last->numFound) {
        L->last->next = new;
        L->last = new;
        L->curr = new;
    } else {
        L->curr = L->first;
        while (L->curr != NULL) {
            if (numFound < L->curr->numFound && numFound >= L->curr->next->numFound) {
                new->next = L->curr->next;
                L->curr->next = new;
                break;
            }
            L->curr = L->curr->next;
        }
    }
    L->nitems++;
}

void printList(List L) {
    L->curr = L->first;
    while (L->curr != NULL) {
        // printf("1\n");
        printf("%s %d\n", L->curr->urlname, L->curr->numFound);
        L->curr = L->curr->next;
        // printf("2\n");
    }
}

void dropList(List L) {
    L->curr = L->first;
    while (L->curr != NULL) {
        matchedList tmp = L->curr;
        L->curr = L->curr->next;
        free(tmp->urlname);
        free(tmp);
    }
    free(L);
}