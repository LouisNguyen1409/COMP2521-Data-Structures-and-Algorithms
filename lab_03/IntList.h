// IntList.h - Interface to the IntList ADT
// Lists of integers

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef INTLIST_H
#define INTLIST_H

#include <stdbool.h>
#include <stdio.h>

typedef struct IntListRep *IntList;

/**
 * Creates a new, empty IntList.
 */
IntList IntListNew(void);

/**
 * Frees all memory associated with an IntList.
 */
void IntListFree(IntList l);

/**
 * Creates an IntList by reading values from a file.
 * Assumes that the file is open for reading.
 */
IntList IntListRead(FILE *in);

/**
 * Prints an IntList to stdout, one integer per line.
 */
void IntListShow(IntList l);

/**
 * Appends an integer to an IntList.
 */
void IntListAppend(IntList l, int v);

/**
 * Inserts an integer into the appropriate place in a sorted IntList,
 * such that the list remains sorted.
 * Assumes that the given list is sorted.
 */
void IntListInsertInOrder(IntList l, int v);

/**
 * Returns the number of elements in an IntList.
 */
int IntListLength(IntList l);

/**
 * Creates a copy of an IntList.
 */
IntList IntListCopy(IntList l);

/**
 * Creates a sorted copy of an IntList.
 */
IntList IntListSortedCopy(IntList l);

/**
 * Checks whether an IntList is sorted in ascending order.
 * Returns true if the list is sorted, and false otherwise.
 */
bool IntListIsSorted(IntList l);

/**
 * Checks the internal consistency of an IntList.
 * Returns true if the list is consistent, and false otherwise.
 */
bool IntListOK(IntList l);

/**
 * Prints an IntList to a file, one integer per line.
 * Assumes that the file is open for writing.
 */
void IntListPrint(IntList l, FILE *out);

#endif

