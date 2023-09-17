// testBst.c

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int main(void) {
	setbuf(stdout, NULL);

	struct node *t = bstNew();

	int value = 0;
	while (scanf("%d", &value) == 1) {
		t = bstInsert(t, value);
	}

	// Display information about constructed tree
	printf("BST:\n");
	bstShow(t);
	printf("\n");

	printf("#nodes:  %d\n", bstNumNodes(t));
	printf("#leaves: %d\n", bstNumLeaves(t));
	printf("Range:   %d\n", bstRange(t));
	printf("\n");

	printf("In-order:    "); bstInOrder(t);    printf("\n");
	printf("Pre-order:   "); bstPreOrder(t);   printf("\n");
	printf("Post-order:  "); bstPostOrder(t);  printf("\n");
	printf("Level-order: "); bstLevelOrder(t); printf("\n");
	printf("\n");

	printf("Deleting all the leaves in the BST...\n");
	t = bstDeleteLeaves(t);
	printf("New BST:\n");
	bstShow(t);
	printf("\n");

	bstFree(t);
}

