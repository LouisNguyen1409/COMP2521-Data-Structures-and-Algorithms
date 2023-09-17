
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "bstree.h"

int bstree_difference(bstree t);

int main(void) {
	bstree t = bstree_read(0);
	printf("\n");
	printf("BST:\n");
	bstree_print(t);

	printf("Minimum difference: ");
	int size = bstree_difference(t);
	printf("%d\n", size);

	bstree_free(t);
}
