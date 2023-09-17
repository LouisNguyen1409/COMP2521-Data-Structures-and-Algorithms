// Implementation of a priority queue of edges

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Pq.h"

#define DEFAULT_CAPACITY 64

struct pq {
	struct edge *items;
	int size;
	int capacity;
};

static void fixUp(Pq pq, int i);
static void fixDown(Pq pq, int i);
static void swap(struct edge *items, int i, int j);

Pq PqNew(void) {
	Pq pq = malloc(sizeof(*pq));
	if (pq == NULL) {
		fprintf(stderr, "Couldn't allocate Pq!\n");
		exit(EXIT_FAILURE);
	}
	
	pq->items = malloc((DEFAULT_CAPACITY + 1) * sizeof(struct edge));
	if (pq->items == NULL) {
		fprintf(stderr, "Couldn't allocate Pq!\n");
		exit(EXIT_FAILURE);
	}
	
	pq->size = 0;
	pq->capacity = DEFAULT_CAPACITY;
	return pq;
}

void PqFree(Pq pq) {
	free(pq->items);
	free(pq);
}

void PqInsert(Pq pq, struct edge e) {
	// If the Pq is full, expand it (i.e., double its capacity)
	if (pq->size == pq->capacity) {
		pq->capacity *= 2;
		pq->items = realloc(
			pq->items,
			(pq->capacity + 1) * sizeof(struct edge)
		);
		if (pq->items == NULL) {
			fprintf(stderr, "Couldn't expand Pq!\n");
			exit(EXIT_FAILURE);
		}
	}
	
	// Add the new item to the end
	pq->size++;
	pq->items[pq->size] = e;
	fixUp(pq, pq->size);
}

static void fixUp(Pq pq, int i) {
	while (i > 1 && pq->items[i].weight < pq->items[i / 2].weight) {
		swap(pq->items, i, i / 2);
		i = i / 2;
	}
}

struct edge PqExtract(Pq pq) {
	assert(pq->size > 0);
	
	struct edge e = pq->items[1];
	pq->items[1] = pq->items[pq->size];
	pq->size--;
	fixDown(pq, 1);
	return e;
}

static void fixDown(Pq pq, int i) {
	struct edge *es = pq->items;
	while (true) {
		int j = i;
		int l = 2 * i;
		int r = 2 * i + 1;
		if (l <= pq->size && es[l].weight < es[j].weight) j = l;
		if (r <= pq->size && es[r].weight < es[j].weight) j = r;
		if (j == i) break;
		swap(pq->items, i, j);
		i = j;
	}
}

bool PqIsEmpty(Pq pq) {
	return (pq->size == 0);
}

void PqShow(Pq pq) {
	printf("#items = %d\n", pq->size);
	printf("Items:");
	for (int i = 1; i <= pq->size; i++) {
		printf(" (v: %d, w: %d, weight: %.2lf)",
		       pq->items[i].v, pq->items[i].w, pq->items[i].weight);
	}
	printf("\n");
}

////////////////////////////////////////////////////////////////////////

static void swap(struct edge *items, int i, int j) {
	struct edge tmp = items[i];
	items[i] = items[j];
	items[j] = tmp;
}
