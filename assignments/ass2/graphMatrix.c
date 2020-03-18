// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "graphMatrix.h"
#include "queue.h"
#include "collectionList.h"

// check validity of Vertex
int validV (Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
// static Edge mkEdge (Graph g, Vertex v, Vertex w)
// {
// 	assert (g != NULL && validV (g, v) && validV (g, w));
// 	Edge new = {v, w}; // struct assignment
// 	g->iList[v].inlinks++;
// 	g->iList[w].outlinks++;
// 	return new;
// }

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge (Graph g, Vertex u, Vertex v)
{
	assert (g != NULL && validV (g, u) && validV (g, v));

	if (g->edges[u][v] != 0 && g->edges[v][u] != 0)
		// an edge already exists; do nothing.
		return;

	g->edges[u][v] = 1;
	// g->edges[v][u] = 1;
	g->iList[u].outlinks++;
	g->iList[v].inlinks++;
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

	new->iList = calloc ((size_t) nV, sizeof(struct infoNode));
	assert (new->iList != NULL);

	new->urls = calloc ((size_t) nV, sizeof (char *));
	assert (new->urls != NULL);

	for (int v = 0; v < nV; v++) {
		new->edges[v] = calloc ((size_t) nV, sizeof (int));
		assert (new->edges[v] != 0);

		new->iList[v].inlinks = 0;
		new->iList[v].outlinks = 0;
		new->iList[v].PR = pow(nV, -1);
		new->iList[v].prevPR = pow(nV, -1);

		new->urls[v] = malloc(sizeof(char)*100);

		for (int i = 0; i < nV; i++) {
			new->edges[v][i] = 0;
		}
	}

	return new;
}

// free memory associated with graph
void dropGraph (Graph g)
{
	assert (g != NULL);
	for (int v = 0; v < g->nV; v++) {
		free(g->urls[v]);
		free(g->edges[v]);
	}
	free(g->iList);
	free(g->urls);
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
	for (int i = dest; pred[i] != -1; i = pred[i]) {
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
