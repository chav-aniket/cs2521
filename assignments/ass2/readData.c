// Created by Aniket Chavan (z5265106) on 22/07/19

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphMatrix.h"
#include "collectionList.h"
#include "readData.h"

CollectionList getCollection() {
    CollectionList cList = newCollectionList();
    FILE *fd;
    char buffer[100];
    char append[5] = ".txt";

    fd = fopen("collection.txt","r");
    if (fd == NULL) {
        printf("Collection.txt doesn't exist");
    } else {
        int i = 0;
        while (fscanf(fd, "%s", buffer) == 1) {
            strcat(buffer, append);
            CollectionListAppend(cList, buffer, i);
            // printf("buffer is %s\n", buffer);
            i++;
        }
    }
    return cList;
}

Graph getGraph(CollectionList L) {
    Graph g = newGraph(returnNitems(L));
    FILE *fd;
    char buffer[100];
    char append[5] = ".txt";

    int start = 0;
    int end = 0;
    setCurrToFirst(L);
    while (!currNull(L)) {
        start = 0;

        fd = fopen(returnFilename(L),"r");

        Vertex u,v;
        u = returnID(L, returnFilename(L));
        strcpy(g->urls[u], returnFilename(L));

        while (fscanf(fd, "%s", buffer) == 1) {
            if (!end && strcmp(buffer, "Section-1") == 0) {
                start = 1;
                continue;
            }
            if (start && strcmp(buffer, "#end") == 0) {
                break;
            }
            if (start) {
                strcat(buffer, append);
                v = returnID(L, buffer);
                if (u == v) continue;
                strcpy(g->urls[v], buffer);

                insertEdge(g, u, v);
            }
        }

        fclose(fd);
        nextNode(L);
    }
    return g;
}