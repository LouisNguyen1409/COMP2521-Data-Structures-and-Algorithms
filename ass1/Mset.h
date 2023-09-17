// Interface to the Multiset ADT
// COMP2521 23T2 Assignment 1

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef MSET_H
#define MSET_H

#include <limits.h>
#include <stdbool.h>

#define UNDEFINED INT_MIN

typedef struct mset *Mset;

struct item {
	int item;
	int count;
};

////////////////////////////////////////////////////////////////////////
// Basic Operations
/**
 * Creates a new empty mset
 */
Mset MsetNew(void);

/**
 * Frees all memory allocated to the given mset
 */
void MsetFree(Mset s);

/**
 * Inserts one of an item into the mset. Does nothing if the item is
 * equal to UNDEFINED.
 */
void MsetInsert(Mset s, int item);

/**
 * Inserts the given amount of an item into the mset. Does nothing if
 * the item is equal to UNDEFINED or the given amount is 0 or less.
 */
void MsetInsertMany(Mset s, int item, int amount);

/**
 * Returns the number of distinct elements in the mset
 */
int MsetSize(Mset s);

/**
 * Returns the sum of counts of all elements in the mset
 */
int MsetTotalCount(Mset s);

/**
 * Returns the count of an item in the mset, or 0 if it doesn't occur in
 * the mset
 */
int MsetGetCount(Mset s, int item);

/**
 * Prints the given mset in the format
 * {(elem1, count1), (elem2, count2), (elem3, count3)}
 * where the elements are in increasing order
 */
void MsetShow(Mset s);

////////////////////////////////////////////////////////////////////////
// Advanced Operations

/**
 * Returns a new mset representing the union of the two msets
 */
Mset MsetUnion(Mset s1, Mset s2);

/**
 * Returns a new mset representing the intersection of two msets
 */
Mset MsetIntersection(Mset s1, Mset s2);

/**
 * Returns a new mset representing the addition of two msets
 */
Mset MsetSum(Mset s1, Mset s2);

/**
 * Returns a new mset representing the difference s1 - s2
 */
Mset MsetDifference(Mset s1, Mset s2);

/**
 * Returns true if the mset s1 is included in the mset s2, and false
 * otherwise
 */
bool MsetIncluded(Mset s1, Mset s2);

/**
 * Returns true if the two given msets are equal, and false otherwise
 */
bool MsetEquals(Mset s1, Mset s2);

/**
 * Stores the k most common elements in the mset into the given items
 * array in decreasing order of count and returns the number of elements
 * stored. Elements with the same count should be stored in increasing
 * order.
 */
int MsetMostCommon(Mset s, int k, struct item items[]);

////////////////////////////////////////////////////////////////////////
// Cursor Operations

typedef struct cursor *MsetCursor;

/**
 * Creates a new cursor positioned at the start of the mset
 */
MsetCursor MsetCursorNew(Mset s);

/**
 * Frees all memory allocated to the given cursor
 */
void MsetCursorFree(MsetCursor cur);

/**
 * Returns the element at the cursor's position and its count, or
 * {UNDEFINED, 0} if the cursor is positioned at the start or end of
 * the mset.
 */
struct item MsetCursorGet(MsetCursor cur);

/**
 * Moves the cursor to the next greatest element, or to the end of the
 * mset if there is no next greatest element. Returns false if the
 * cursor is now at the end of the mset, and true otherwise.
 */
bool MsetCursorNext(MsetCursor cur);

/**
 * Moves the cursor to the next smallest element, or to the start of the
 * mset if there is no next smallest element. Returns false if the
 * cursor is now at the start of the mset, and true otherwise.
 */
bool MsetCursorPrev(MsetCursor cur);

////////////////////////////////////////////////////////////////////////

#endif

