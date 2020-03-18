// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Graph.h"
#include "Queue.h"

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int nV;		 // #vertices
	int nE;		 // #edges
	int **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV (Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
static Edge mkEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	Edge new = {v, w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge (Graph g, Vertex v, Vertex w, int wt)
{
	assert (g != NULL && validV (g, v) && validV (g, w));

	if (g->edges[v][w] != 0 && g->edges[w][v] != 0)
		// an edge already exists; do nothing.
		return;

	g->edges[v][w] = wt;
	g->edges[w][v] = wt;
	g->nE++;
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	if (g->edges[v][w] == 0 && g->edges[w][v] == 0)
		// an edge doesn't exist; do nothing.
		return;
	g->edges[v][w] = 0;
	g->edges[w][v] = 0;
	g->nE--;
}

// create an empty graph
Graph newGraph (int nV)
{
	assert (nV > 0);

	GraphRep *new = malloc (sizeof *new);
	assert (new != NULL);
	*new = (GraphRep){ .nV = nV, .nE = 0 };

	new->edges = calloc ((size_t) nV, sizeof (int *));
	assert (new->edges != NULL);
	for (int v = 0; v < nV; v++) {
		new->edges[v] = calloc ((size_t) nV, sizeof (int));
		assert (new->edges[v] != 0);
	}

	return new;
}

// free memory associated with graph
void dropGraph (Graph g)
{
	assert (g != NULL);
	for (int v = 0; v < g->nV; v++)
		free (g->edges[v]);
	free (g->edges);
	free (g);
}

// display graph, using names for vertices
void showGraph (Graph g, char **names)
{
	assert (g != NULL);
	printf ("#vertices=%d, #edges=%d\n\n", g->nV, g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf ("%d %s\n", v, names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf ("\t%s (%d)\n", names[w], g->edges[v][w]);
			}
		}
		printf ("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath (Graph g, Vertex src, Vertex dest, int max, int *path)
{
	assert (g != NULL);

	if (ItemEQ(src, dest)) {
		path[0] = dest;
		return 1;
	}

	bool found = false;
	int *distance = calloc(g->nV, sizeof(int));
	Vertex *visited = calloc(g->nV, sizeof(int));
	Vertex *pred = calloc(g->nV, sizeof(int));

	for (int i = 0; i < g->nV; i++) {
		pred[i] = visited[i] = -1;
	}


	Queue q = newQueue();
	QueueJoin(q, src);

	Vertex v, w;
	visited[src] = 1;
	while (!found && !QueueIsEmpty(q)) {
		v = QueueLeave(q);

		if (ItemEQ(v, dest)) {
			found = true;
		} else {
			for (w = 0; w < g->nV; w++) {
				if (validV(g,w) && (visited[w] == -1)
					&& (g->edges[w][v] < max)) {
						if (w == dest) found = true;
						visited[w] = 1;
						pred[w] = v;
						distance[w] = distance[v] + 1;
						QueueJoin(q, w);
				}
			}
		}
	}
	
	if (!found) {
		free(visited);
		free(distance);
		free(pred);
		dropQueue(q);
		return 0;
	}

	int j = distance[dest];
	path[0] = src;
	// printf("distance[dest] = %d\n", distance[dest]);
	// printf("pred[src] = %d\n", pred[src]);
	for (int i = dest; pred[i] != -1; i = pred[i]) {
		// printf("i = %d\n", i);
		// printf("pred[i] = %d\n", pred[i]);
		// if (pred[i] != -1)
		// 	path[distance[dest]] = dest;
		path[j] = i;
		j--;
		if (j < 0) break;
	}

	int dist = distance[dest];
	
	free(visited);
	free(distance);
	free(pred);
	dropQueue(q);
	return dist+1;
}
