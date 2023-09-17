/**
 * Written by James Davidson
 * https://gist.github.com/jedavidson/b8dfd82f62616a84246e4a6dd8105751
 * 
 * Simple graph implementation. Can work as either directed/undirected graph.
 *
 * To create a graph from stdin, enter input in the following format:
 *   - First line should be the number of vertices in the graph
 *   - Every line that follows should be of the form "u -> v"
 *
 * e.g. 5
 *      0 -> 1
 *      1 -> 2
 *      2 -> 3
 */


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "Graph.h"


/**
 * GRAPH INTERFACE
 * These are the types and functions you have access to.
 * You are free to use any of them.
 */


/** Return the number of vertices in the graph. */
int   numVertices(Graph g);

/** Check whether two vertices are connected in a graph. */
bool  adjacent(Graph g, Vertex u, Vertex v);

/** Insert an edge between two vertices into a graph. */
static void  insertEdge(Graph g, Vertex u, Vertex v);

/** Remove an edge between two vertices into a graph. */
// static void  removeEdge(Graph g, Vertex u, Vertex v);

/** Build a graph from input on stdin. Ignore this function! */
Graph buildGraph(void);

/** Free all memory associated with a graph. Ignore this function! */
void  freeGraph(Graph g);


/**
 * IGNORE EVERYTHING BELOW THIS LINE
 */


// Remove this line if you want an undirected graph.
// #define DIRECTED


Graph buildGraph(void) {
    Graph g = malloc(sizeof(*g));
    if (g == NULL)
        exit(EXIT_FAILURE);;

    int nV;
    scanf("%d", &nV);

    g->_nV = nV;
    g->_adjMatrix = malloc(nV * sizeof(bool *));
    if (g->_adjMatrix == NULL)
        exit(EXIT_FAILURE);;

    for (Vertex v = 0; v < nV; v++) {
        g->_adjMatrix[v] = calloc(nV, sizeof(bool));
        if (g->_adjMatrix[v] == NULL)
            exit(EXIT_FAILURE);;
    }

    int u, v;
#ifdef DIRECTED
    while (scanf("%d -> %d", &u, &v) == 2)
        insertEdge(g, u, v);
#endif
#ifndef DIRECTED
    while (scanf("%d <-> %d", &u, &v) == 2)
        insertEdge(g, u, v);
#endif

    return g;
}

static bool isVertex(Graph g, Vertex v) {
    return 0 <= v && v < g->_nV;
}

void insertEdge(Graph g, Vertex u, Vertex v) {
    if (isVertex(g, u) && isVertex(g, v)) {
        g->_adjMatrix[u][v] = true;
#ifndef DIRECTED
        g->_adjMatrix[v][u] = true;
#endif
    }
}

// static void removeEdge(Graph g, Vertex u, Vertex v) {
//     if (isVertex(g, u) && isVertex(g, v)) {
//         g->_adjMatrix[u][v] = false;
// #ifndef DIRECTED
//         g->_adjMatrix[v][u] = false;
// #endif
//     }
// }

int numVertices(Graph g) {
    return g->_nV;
}

bool adjacent(Graph g, Vertex u, Vertex v) {
    return isVertex(g, u) && isVertex(g, v)
#ifndef DIRECTED
        && g->_adjMatrix[v][u]
#endif
        && g->_adjMatrix[u][v];
}

void freeGraph(Graph g) {
    free(g->_adjMatrix);
    free(g);
}
