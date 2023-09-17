// List.h - interface to List ADT

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct list *List;

/**
 * Creates a new empty list
 */
List ListNew(void);

/**
 * Frees all memory allocated to the list
 */
void ListFree(List l);

/**
 * Adds an element to the start of the list
 */
void ListAddStart(List l, int elem);

/**
 * Adds an element to the end of the list
 */
void ListAddEnd(List l, int elem);

/**
 * Deletes an element from the start of the list and returns it
 * Assumes that the list is not empty
 */
int ListDeleteStart(List l);

/**
 * Deletes an element from the end of the list and returns it
 * Assumes that the list is not empty
 */
int ListDeleteEnd(List l);

/**
 * Returns the first element in the list
 * Assumes that the list is not empty
 */
int ListFirst(List l);

/**
 * Returns the last element in the list
 * Assumes that the list is not empty
 */
int ListLast(List l);

/**
 * Returns the number of elements in the list
 */
int ListSize(List l);

/**
 * Returns true if the given element is in the list, and false otherwise
 */
bool ListContains(List l, int elem);

/**
 * Prints the given list to stdout
 */
void ListShow(List l);

#endif

