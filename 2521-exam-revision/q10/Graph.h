// Interface to the directed graph ADT

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct adjNode *AdjList;
struct adjNode {
    int v;
    AdjList next;
};

typedef struct graph *Graph;
struct graph {
    AdjList *edges;  // array of lists
    int      nV;     // #vertices
    int      nE;     // #edges
};

// vertices are ints
typedef int Vertex;

// Create a new graph
Graph GraphNew(int nV);

// Frees all memory associated with the given graph
void GraphFree(Graph g);

// Number of vertices in the given graph
int GraphNumVertices(Graph g);

// Inserts a directed edge from 'v' to 'w'
void GraphInsertEdge(Graph g, Vertex v, Vertex w);

// Prints the given graph to stdout
void GraphShow(Graph g);

#endif

