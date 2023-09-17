// Main program for testing maxDegreeDiff

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int maxDegreeDiff(Graph g);

int main(void) {
    int nV = 0;
    if (scanf("%d", &nV) != 1) {
        printf("error: failed to read number of vertices\n");
        return EXIT_FAILURE;
    }

    Graph g = GraphNew(nV);
    int v, w;
    while (scanf("%d %d", &v, &w) == 2) {
        GraphInsertEdge(g, v, w);
    }

    GraphShow(g);
    printf("\n");

    int maxDiff = maxDegreeDiff(g);

    printf("maximum absolute degree difference: %d\n", maxDiff);

    GraphFree(g);
}

