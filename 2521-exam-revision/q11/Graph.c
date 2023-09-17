// Implementation of the Graph ADT

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"

static bool validVertex(Graph g, Vertex v);

// create an empty graph
Graph GraphNew(int nV) {
    assert(nV > 0);

    Graph g = malloc(sizeof(*g));
    if (g == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    g->nV = nV;
    g->numStdEdges = 0;
    g->numFastEdges = 0;

    g->stdEdges = calloc(nV, sizeof(bool *));
    if (g->stdEdges == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nV; i++) {
        g->stdEdges[i] = calloc(nV, sizeof(bool));
        if (g->stdEdges[i] == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
    }

    g->fastEdges = calloc(nV, sizeof(bool *));
    if (g->fastEdges == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nV; i++) {
        g->fastEdges[i] = calloc(nV, sizeof(bool));
        if (g->fastEdges[i] == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
    }

    return g;
}

void GraphAddEdge(Graph g, Edge e, Road t) {
    assert(validVertex(g, e.v));
    assert(validVertex(g, e.w));

    switch (t) {
        case NO_ROAD:
            break;

        case STD_ROAD:
            if (g->stdEdges[e.v][e.w]) return;
            g->stdEdges[e.v][e.w] = 1;
            g->stdEdges[e.w][e.v] = 1;
            g->numStdEdges++;
            break;

        case FAST_ROAD:
            if (g->fastEdges[e.v][e.w]) return;
            g->fastEdges[e.v][e.w] = 1;
            g->fastEdges[e.w][e.v] = 1;
            g->numFastEdges++;
            break;
    }
}

void GraphRemoveEdge(Graph g, Edge e, Road t) {
    assert(validVertex(g, e.v));
    assert(validVertex(g, e.w));

    switch (t) {
        case NO_ROAD:
            break;

        case STD_ROAD:
            if (!g->stdEdges[e.v][e.w]) return;
            g->stdEdges[e.v][e.w] = 0;
            g->stdEdges[e.w][e.v] = 0;
            g->numStdEdges--;
            break;

        case FAST_ROAD:
            if (!g->fastEdges[e.v][e.w]) return;
            g->fastEdges[e.v][e.w] = 0;
            g->fastEdges[e.w][e.v] = 0;
            g->numFastEdges--;
            break;
    }
}

void GraphFree(Graph g) {
    for (int i = 0; i < g->nV; i++) {
        free(g->stdEdges[i]);
        free(g->fastEdges[i]);
    }

    free(g->stdEdges);
    free(g->fastEdges);
    free(g);
}

// show one n x n edge matrix
static void showEdges(bool **edges, int nV) {
    for (int v = 0; v < nV; v++) {
        printf("%-2d", v);
        for (int w = 0; w < nV; w++) {
            if (edges[v][w]) {
                printf(" %d", w);
            }
        }
        printf("\n");
    }
}

// display a graph (not pretty)
void GraphShow(Graph g) {
    printf(
        "Graph has %d vertices, %d STD_ROADs, %d FAST_ROADs\n",
        g->nV, g->numStdEdges, g->numFastEdges
    );

    printf("\nV  STD Connections\n");
    printf(  "-- ---------------\n");
    showEdges(g->stdEdges, g->nV);

    printf("\nV  FAST Connections\n");
    printf(  "-- ----------------\n");
    showEdges(g->fastEdges, g->nV);

    printf("\n");
}

// check validity of vertex_t
static bool validVertex(Graph g, Vertex v) {
    return (v >= 0 && v < g->nV);
}

