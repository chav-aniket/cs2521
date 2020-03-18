// Graph.h ... interface to Graph ADT
// Written by John Shepherd, March 2013

#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H

#include <stdio.h>

#include "collectionList.h"

struct infoNode {
	double inlinks;
	double outlinks;
	double PR;
	double prevPR;
};

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int nV;		 // #vertices
	int nE;		 // #edges
	int **edges; // matrix of weights (0 == no edge)
	// CollectionList L;
	char **urls;
	struct infoNode *iList;
} GraphRep;

typedef int Vertex;

#define ItemCopy(i) (i)
#define ItemEQ(i1, i2) ((i1) == (i2))
#define ItemShow(i) printf ("%d", (i))

// graph representation is hidden
typedef struct GraphRep *Graph;

// vertices denoted by integers 0..N-1
int validV (Graph, Vertex); // validity check

// edges are pairs of vertices (end-points)
typedef struct {
	Vertex v;
	Vertex w;
} Edge;
void insertEdge (Graph, Vertex, Vertex);
void removeEdge (Graph, Vertex, Vertex);

// operations on graphs
Graph newGraph (int nV);
void dropGraph (Graph);
Graph makeGraph (int, int **);
void showGraph (Graph, char **);
int findPath (Graph, Vertex, Vertex, int, int *);

#endif
