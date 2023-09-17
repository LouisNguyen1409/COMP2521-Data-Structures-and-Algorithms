// Priority queue of edges
// Edges with smaller weight have higher priority

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef PQ_H
#define PQ_H

#include <stdbool.h>

#include "Graph.h"

typedef struct pq *Pq;

/**
 * Creates a new priority queue
 * Complexity: O(1)
 */
Pq   PqNew(void);

/**
 * Frees all memory associated with the given priority queue
 * Complexity: O(1)
 */
void PqFree(Pq pq);

/**
 * Adds an edge to the priority queue
 * Amortised complexity: O(log n)
 */
void PqInsert(Pq pq, struct edge e);

/**
 * Removes and returns the edge with the smallest weight from the
 * priority queue. If multiple edges have the same smallest weight, one
 * of them will be removed.
 * Complexity: O(log n)
 */
struct edge PqExtract(Pq pq);

/**
 * Returns true if the given priority queue is empty, or false otherwise
 * Complexity: O(1)
 */
bool PqIsEmpty(Pq pq);

/**
 * Prints the given priority queue to stdout for debugging purposes
 */
void PqShow(Pq pq);

#endif
