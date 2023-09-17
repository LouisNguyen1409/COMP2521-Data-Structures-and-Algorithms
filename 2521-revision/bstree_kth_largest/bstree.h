// Header file for BST exercises

#ifndef BSTREE_H
#define BSTREE_H

#define MAX_LINE_LEN 1048576
#define MAX_BST_SIZE 131072

typedef struct _bstree *bstree;
struct _bstree{
	int value;
	bstree left;
	bstree right;
};

bstree bstree_create(int num_elems);
void print_bst(bstree t);
void bstree_free(bstree t);

int kthlargest(bstree t, int k);

#endif
