
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
static bool check_valid(Vertex v, Vertex vs[], int size);

int dayTrip(Graph g, Vertex s, Vertex vs[]) {
    int reach_vertex = 0;
    for (int i = 0; i < g->nV; i++) {
        if (g->stdEdges[s][i] == 1 && check_valid(i, vs, reach_vertex) == true) {
            vs[reach_vertex] = i;
            reach_vertex += 1;
        }
    }
    for (int i = 0; i < g->nV; i++) {
        if(g->fastEdges[s][i] == 1) {
            if (check_valid(i, vs, reach_vertex) == true) {
                vs[reach_vertex] = i;
                reach_vertex += 1;
            }
            for (int j = 0; j < g->nV; j++) {
                if (g->fastEdges[i][j] == 1 && check_valid(j, vs, reach_vertex) == true && j != s) {
                    vs[reach_vertex] = j;
                    reach_vertex += 1;
                }
            }
        }
    }
    return reach_vertex;
}

static bool check_valid(Vertex v, Vertex vs[], int size) {
    for (int i = 0; i < size; i++) {
        if (vs[i] == v) {
            return false;
        }
    }
    return true;
}
