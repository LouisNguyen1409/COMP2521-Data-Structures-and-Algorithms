// Implementation of the directed graph ADT using adjacency lists

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

static void freeAdjList(AdjList l);
static bool inAdjList(AdjList l, int v);
static AdjList adjListInsert(AdjList l, int v);
static AdjList newAdjNode(int v);
static void showAdjList(AdjList l);

static bool validVertex(Graph g, Vertex v);

Graph GraphNew(int nV) {
    assert(nV > 0);

    Graph g = malloc(sizeof(*g));
    if (g == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    g->nV = nV;
    g->nE = 0;

    // allocate memory for array of lists
    g->edges = calloc(nV, sizeof(AdjList));
    if (g->edges == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    return g;
}

void GraphFree(Graph g) {
    for (int i = 0; i < g->nV; i++) {
        freeAdjList(g->edges[i]);
    }
    free(g->edges);
    free(g);
}

static void freeAdjList(AdjList l) {
    AdjList curr = l;
    while (curr != NULL) {
        AdjList temp = curr;
        curr = curr->next;
        free(temp);
    }
}

int GraphNumVertices(Graph g) {
    return g->nV;
}

void GraphInsertEdge(Graph g, int v, int w) {
    assert(validVertex(g, v));
    assert(validVertex(g, w));

    if (!inAdjList(g->edges[v], w)) {
        g->edges[v] = adjListInsert(g->edges[v], w);
        g->nE++;
    }
}

static bool inAdjList(AdjList l, int v) {
    for (AdjList n = l; n != NULL && n->v <= v; n = n->next) {
        if (n->v == v) {
            return true;
        }
    }
    return false;
}

static AdjList adjListInsert(AdjList l, int v) {
    if (l == NULL || v < l->v) {
        AdjList new = newAdjNode(v);
        new->next = l;
        return new;
    } else if (v == l->v) {
        return l;
    } else {
        l->next = adjListInsert(l->next, v);
        return l;
    }
}

static AdjList newAdjNode(int v) {
    AdjList n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    n->v = v;
    n->next = NULL;
    return n;
}

void GraphShow(Graph g) {
    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    printf("Edges:\n");
    for (int i = 0; i < g->nV; i++) {
        printf(" %d: ", i);
        showAdjList(g->edges[i]);
    }
}

static void showAdjList(AdjList l) {
    for (AdjList curr = l; curr != NULL; curr = curr->next) {
        printf("%d", curr->v);
        if (curr->next != NULL) {
            printf(" ");
        }
    }
    printf("\n");
}

// Check if vertex is valid in a graph
static bool validVertex(Graph g, Vertex v) {
    return (v >= 0 && v < g->nV);
}

