// Created by Aniket Chavan (z5265106) on 26/07/19

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "searchPagerank.h"
// #include "collectionList.h"
#include "readData.h"

#define MAX_LINE_LINE 1000
#define MAX_NAME_LINE 1000

int main (int argc, char *argv[]) {
    List L = findMatchedUrls("invertedIndex.txt", argv, argc);
    // printf("ORIGINAL LIST: \n");
    // printList(L);

    List oL = newList();
    L->curr = L->first;
    while (L->curr != NULL) {
        orderedListAppend(oL, L->curr->urlname, L->curr->numFound);
        L->curr = L->curr->next;
    }
    dropList(L);

    // printf("SORTED LIST: \n");
    // printList(oL);
    
    // printf("PR SORTED LIST: \n");
    findPagerank("pagerankList.txt", oL);
    // printf("PRINTED\n");
    // printList(oL);

    // dropList(oL);
    return 1;
}

List findMatchedUrls(char *filename, char *queryWords[], int args) {
    List L = newList();
    
    char line[MAX_LINE_LINE];
    char *buff;

    FILE *fd;
    fd = fopen(filename, "r");

    while (fgets(line, MAX_LINE_LINE, fd) != NULL) {
        buff = strtok(line, " ");
        // printf("buff is %s\n", buff);
        for (int i = 1; i < args; i++) {
            // printf("queryWords[%d] is %s\n", i, queryWords[i]);
            if (strcmp(buff, queryWords[i]) == 0) {
                buff = strtok(NULL, " ");
                while (buff != NULL) {
                    // printf("buff is %s\n", buff);
                    if (strcmp(buff,"\n") == 0) break;
                    listAppend(L, buff);
                    buff = strtok(NULL, " ");
                }
            }
        }
    }

    fclose(fd);
    return L;
}

void findPagerank(char *filename, List L) {
    char line[MAX_LINE_LINE];
    char *buff;
    FILE *fd;
    fd = fopen(filename, "r");

    while (fgets(line, MAX_LINE_LINE, fd) != NULL) {
        buff = strtok(line, ", ");
            // printf("queryWords[%d] is %s\n", i, queryWords[i]);
        L->curr = L->first;
        while (L->curr != NULL) {
            if (strcmp(buff, L->curr->urlname) == 0) {
                buff = strtok(NULL, ", ");
                buff = strtok(NULL, ", ");
                L->curr->PR = atof(buff);
                // printf("PR is %lf\n", L->curr->PR);
            }
            L->curr = L->curr->next;
        }
    }
    fclose(fd);

    int nswaps = 1;

    // Bubble Sorting the linked list to sort by PR
    while (nswaps > 0) {
        nswaps = 0;
        L->curr = L->first;
        if (L->first->numFound == L->first->next->numFound) {
            if (L->first->PR < L->first->next->PR) {
                matchedList tmp = L->first->next;
                L->first->next = tmp->next;
                tmp->next = L->first;
                L->first = tmp;
                nswaps++;
            }
        }
        // 
        L->curr = L->first;
        while (L->curr->next->next != NULL) {
            if (L->curr->next->numFound == L->curr->next->next->numFound) {
                if (L->curr->next->PR < L->curr->next->next->PR) {
                    // printf("Swapping %s with %s\n", L->curr->urlname, L->curr->next->urlname);
                    matchedList tmp = L->curr->next->next;
                    // printf("tmp = %s\n", L->curr->next->urlname);
                    L->curr->next->next = tmp->next;
                    // printf("L->curr->next = %s\n", tmp->next->urlname);
                    tmp->next = L->curr->next;
                    // printf("tmp->next = %s\n", L->curr->urlname);
                    L->curr->next = tmp;
                    // printf("L->curr = %s\n", tmp->urlname);
                    nswaps++;
                }
            }
            L->curr = L->curr->next;
        }
    }

    L->curr = L->first;
    while (L->curr != NULL) {
        fprintf(stdout, "%s\n", L->curr->urlname);
        L->curr = L->curr->next;
    }
}