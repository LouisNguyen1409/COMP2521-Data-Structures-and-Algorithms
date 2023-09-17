// BST definition and interface to utility functions

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef BSTREE_H
#define BSTREE_H

typedef struct node *BSTree;
struct node {
    int key;
    BSTree left;
    BSTree right;
};

// Creates a new empty BST
BSTree BSTreeNew(void);

// Frees all memory associated with the given BST
void BSTreeFree(BSTree);

// Prints a BST to stdout
void BSTreeShow(BSTree);

// Inserts a new key into a BST
BSTree BSTreeInsert(BSTree, int key);

// Creates a BST by reading integer values from a line 
BSTree BSTreeRead(char *line);

#endif

