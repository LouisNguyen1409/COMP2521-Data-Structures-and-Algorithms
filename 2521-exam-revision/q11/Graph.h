// Interface to the Graph ADT

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct graph *Graph;

// graph representation (adjacency matrix)
struct graph {
    int nV;            // #vertices
    int numStdEdges;   // #STD_ROAD edges
    int numFastEdges;  // #FAST_ROAD edges
    bool **stdEdges;   // matrix of STD_ROAD edges
    bool **fastEdges;  // matrix of FAST_ROAD edges
};

typedef enum {
	NO_ROAD = ' ',
	STD_ROAD = 's',
	FAST_ROAD = 'f',
} Road;

// vertices denoted by integers 0..N-1
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct edge {
    Vertex v;
    Vertex w;
} Edge;

// operations on graphs
Graph GraphNew(int nV);
void GraphAddEdge(Graph g, Edge e, Road t);
void GraphRemoveEdge(Graph g, Edge e, Road t);
void GraphFree(Graph g);
void GraphShow(Graph g);

#endif
