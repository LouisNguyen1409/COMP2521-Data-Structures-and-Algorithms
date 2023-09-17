
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "bstree.h"

int main(void) {
    int i;
    scanf("%d", &i);
	bstree t = bstree_create(i);
    scanf("%d", &i);
    printf("%d\n", kthlargest(t, i));
	bstree_free(t);
}
