// Created by Aniket Chavan (z5265106) on 22/07/19
#ifndef PAGERANK_H
#define PAGERANK_H

#include <stdio.h>
#include "graphMatrix.h"

void PageRankW(Graph g, int maxiterations, double diffPR, double d);

double wIn(Graph g, Vertex u, Vertex v);

double wOut(Graph g, Vertex u, Vertex v);

double calcPR(Graph g, Vertex v, double d, int t);

// double calcDiff(Graph g, double d, int t, int diffPR);

#endif