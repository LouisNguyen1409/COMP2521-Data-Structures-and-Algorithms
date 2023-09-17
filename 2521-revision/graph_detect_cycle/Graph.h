// Header file for BST exercises

#ifndef GRAPH_H
#define GRAPH_H

#define MAX_NUM_VERTICES 1024

/** Graph representation. You shouldn't need to modify it. */
typedef struct graph *Graph;
struct graph {
    bool **_adjMatrix;
    int    _nV;
};

/** All vertices in the graph are nonnegative integers. */
typedef unsigned int Vertex;

Graph buildGraph(void);
void  freeGraph(Graph g);

int   numVertices(Graph g);
bool  adjacent(Graph g, Vertex u, Vertex v);

bool graphDetectCycle(Graph g);

#endif

