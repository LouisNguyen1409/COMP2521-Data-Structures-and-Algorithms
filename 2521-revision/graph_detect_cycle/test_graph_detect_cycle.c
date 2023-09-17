/**
 * Build an undirected unweighted graph with at least one edge
 * from stdin.
 * First line: n the number of vertices in your graph
 * Following lines: each line contains the two vertices connected
 * by an edge. Vertices are numbered 0 to n-1 inclusive.
 *
 * Usage:
    $ dcc test_graph_detect_cycle.c graph_detect_cycle.c Graph.c -o test_graph_detect_cycle
    $ ./test_graph_detect_cycle
    3
    0 <-> 1
    1 <-> 2
    
 * Ctrl + D to end input.
 * 
 * Note: You do not have to modify this file to complete
 * this exercise.
 */ 

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int main(void) {


    Graph g = buildGraph();

    // Add anything you want to read in after reading in the graph here.
    // ...

    // Call the function they have to implement.
    // If it returns something, capture that return value.
    bool hasCycle = graphDetectCycle(g);

    // Print the return value from the function if there is one.
    if (hasCycle) {
		printf("Has cycle\n");
	} else {
		printf("Does not have cycle\n");
	}

    // Do any cleanup needed here.
    freeGraph(g);
    
    return EXIT_SUCCESS;
}