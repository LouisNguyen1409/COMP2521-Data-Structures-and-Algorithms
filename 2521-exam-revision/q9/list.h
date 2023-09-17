// Linked list definition and interface to utility functions

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node *List;

struct node {
    int value;
    List next;
};

// Creates a new empty list
List ListNew(void);

// Frees all memory associated with the given list
void ListFree(List l);

// Inserts a value at the end of the given list
// Returns the beginning of the updated list
List ListInsert(List l, int value);

// Prints a list to stdout
void ListShow(List l);

// Prints the ascending prefix of a list to stdout
void ListShowAscending(List l);

// Creates a list by reading integer values from a file
List ListRead(FILE *fp);

#endif

