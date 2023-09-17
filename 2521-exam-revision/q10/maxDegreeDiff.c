
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int maxDegreeDiff(Graph g) {
    int *diff = calloc(g->nV, sizeof(int));
    for (int i = 0; i < g->nV; i++) {
        AdjList curr = g->edges[i];
        while (curr != NULL) {
            diff[curr->v] += 1;
            diff[i] -= 1;
            curr = curr->next;
        }
    }

    int max = 0;
    for (int i = 0; i < g->nV; i++) {
        if (abs(diff[i]) > max) {
            max = abs(diff[i]);
        }
    }
    return max;
}

