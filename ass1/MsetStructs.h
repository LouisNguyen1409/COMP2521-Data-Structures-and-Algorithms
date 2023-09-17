// COMP2521 23T2 Assignment 1

#ifndef MSET_STRUCTS_H
#define MSET_STRUCTS_H

// DO NOT CHANGE THE NAME OF THIS STRUCT
struct node {
	int item;           // DO NOT CHANGE/REMOVE THIS FIELD
	int count;          // DO NOT CHANGE/REMOVE THIS FIELD
	struct node *left;  // DO NOT CHANGE/REMOVE THIS FIELD
	struct node *right; // DO NOT CHANGE/REMOVE THIS FIELD
	// You may add more fields here if needed
	int height;
	struct ll *node;
};

// DO NOT CHANGE THE NAME OF THIS STRUCT
struct mset {
	struct node *tree;  // DO NOT CHANGE/REMOVE THIS FIELD;
	// You may add more fields here if needed
	int size;
	int total_count;
	struct ll *head;
};

// You may define more structs here if needed
struct ll { 
	struct ll *pre;
	struct ll *next;
	int item;
	int count;
};
////////////////////////////////////////////////////////////////////////
// Cursors

struct cursor {
	// You may add more fields here if needed
	struct ll *curr;
	struct ll *pre;
	struct ll *next;
};

////////////////////////////////////////////////////////////////////////

#endif

