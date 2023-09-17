// Main program for testing dayTrip

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int dayTrip(Graph g, Vertex s, Vertex vs[]);

static int cmp(const void *a, const void *b);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s <graph file> <start vertex>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *graphFile = argv[1];
    Vertex startVertex = atoi(argv[2]);

    FILE *in = fopen(graphFile, "r");
    if (in == NULL) {
        fprintf(stderr, "error: failed to open '%s'\n", graphFile);
        exit(EXIT_FAILURE);
    }

    int nV = 0;
    if (fscanf(in, "%d", &nV) != 1) {
        fprintf(stderr, "error: failed to read number of vertices\n");
        exit(EXIT_FAILURE);
    }

    Graph g = GraphNew(nV);

    int v, w;
    char roadType;
    while (fscanf(in, "%d %d %c", &v, &w, &roadType) == 3) {
        GraphAddEdge(g, (Edge){v, w}, (Road) roadType);
    }
    fclose(in);

    GraphShow(g);

    // find vertices reachable via one day's drive from startVertex
    Vertex *vertices = calloc(nV, sizeof(Vertex));
    int numVertices = dayTrip(g, startVertex, vertices);

    qsort(vertices, numVertices, sizeof(Vertex), cmp);
    printf("day trips from %d:", startVertex);
    for (int i = 0; i < numVertices; i++) {
        printf(" %d", vertices[i]);
    }
    printf("\n");

    free(vertices);
    GraphFree(g);
}

// comparison function for qsort
static int cmp(const void *a, const void *b) {
    const int *ap = (const int *) a;
    const int *bp = (const int *) b;
    return (*ap) - (*bp);
}

