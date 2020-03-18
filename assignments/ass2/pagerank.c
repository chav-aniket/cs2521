// Created by Aniket Chavan (z5265106) on 22/07/19

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "graphMatrix.h"
#include "readData.h"
#include "collectionList.h"
#include "pagerank.h"

int main(int argc, char *argv[]) {

    assert(argc > 1);

    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxiterations = atoi(argv[3]);

    CollectionList L = getCollection();
    Graph g = getGraph(L);
    
    // UNCOMMENT TO SHOW GRAPH
    // showGraph(g, g->urls);

    // Sets all inlinks and outlinks that are zero to 0.5

    for (Vertex v = 0; v < g->nV; v++) {
        if (g->iList[v].outlinks == 0)
            g->iList[v].outlinks = 0.5;
        if (g->iList[v].inlinks == 0)
            g->iList[v].inlinks = 0.5;
    }

    // Calling PageRankW to get all Pageranks

    PageRankW(g, maxiterations, diffPR, d);

    // Printing out the URL's to the file in order of PageRank

    FILE *fd;
    fd = fopen("pagerankList.txt","w");

    Vertex max = 0;
    double maxPR = 0;
    double prevPR = 10000;

    for (int i = 0; i < g->nV; i++) {
        maxPR = 0;
        for (Vertex v = 0; v < g->nV; v++) {
            if (g->iList[v].PR < prevPR && g->iList[v].PR > maxPR) {
                maxPR = g->iList[v].PR;
                max = v;
            }
        }
        int outlinks = g->iList[max].outlinks;
        fprintf(fd, "%s, %d, %.7lf\n", g->urls[max], outlinks, g->iList[max].PR);
        printf("%s, %d, %.7lf\n", g->urls[max], outlinks, g->iList[max].PR);
        prevPR = g->iList[max].PR;
    }
    fclose(fd);

    freeCollectionList(L);
    dropGraph(g);
    return 1;
}

void PageRankW(Graph g, int maxiterations, double diffPR, double d) {
    int t = 0; // t is iteration counter
    double diff = diffPR;

    while (t < maxiterations && diff >= diffPR) {
        diff = 0;
        for (Vertex v = 0; v < g->nV && validV(g, v); v++) {
            g->iList[v].PR = calcPR(g, v, d, t+1);
            diff += fabs(g->iList[v].PR - g->iList[v].prevPR);
            g->iList[v].prevPR = g->iList[v].PR;
        }
        t++;
    }
}

double wIn(Graph g, Vertex u, Vertex v) {
    double sum = 0;
    for (Vertex w = 0; w < g->nV; w++) {
        if (g->edges[u][w]) {
            sum += g->iList[w].inlinks;
        }
    }
    return g->iList[v].inlinks*pow(sum, -1);
}

double wOut(Graph g, Vertex u, Vertex v) {
    double sum = 0;
    for (Vertex w = 0; w < g->nV; w++) {
        if (g->edges[u][w]) {
            sum += g->iList[w].outlinks;
        }
    }
    return g->iList[v].outlinks*pow(sum, -1);
}

double calcPR(Graph g, Vertex v, double d, int t) {
    if (t == 0) return pow(g->nV, -1);

    double sum = 0;
    for (Vertex w = 0; w < g->nV; w++) {
        if (g->edges[w][v]) {
            sum += calcPR(g, w, d, t-1) * 
                    wIn(g, w, v) * wOut(g, w, v);
        }
    }

    return ((1-d)*pow(g->nV, -1))+(d*sum);
}

// double calcDiff(Graph g, double d, int t, int diffPR) {
//     double sum = 0;
//     for (Vertex v = 0; v < g->nV; v++) {
//         sum += fabs(g->iList[v].PR - g->iList[v].prevPR);
//     }
//     return sum;
// }
