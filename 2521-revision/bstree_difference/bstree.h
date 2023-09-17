// Header file for BST exercises

#ifndef BSTREE_H
#define BSTREE_H

#define MAX_LINE_LEN 1048576
#define MAX_BST_SIZE 131072

typedef struct bstree_node *bstree;
struct bstree_node {
	int value;
	bstree left;
	bstree right;
	bstree parent;
};

////////////////////////////////////////////////////////////////////////
// Utility Functions

// You shouldn't use any of these functions in your code. (You shouldn't
// need to.)

/**
 * Reads  in a line of integers representing the preorder traversal of a
 * BST from stdin and converts it into a BST.
 * Assumes  that the line consists entirely of space-separated integers,
 * is  no  longer  than  8096 characters, and contains no more than 1024
 * integers.
 * If  only one BST needs to be read in for a particular exercise, bstNo
 * should  be set to 0. Otherwise, bstNo specifies the number of the BST
 * that is being read in (1, 2, ...).
 */
bstree bstree_read(int bst_no);

void bstree_print(bstree t);

void bstree_free(bstree t);

#endif
