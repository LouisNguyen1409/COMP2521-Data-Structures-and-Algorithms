// Main program for testing minDiff

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int minDiff(BSTree t, int l);

int main(int argc, char *argv[]) {
    char buffer[1024];

    char *line1 = fgets(buffer, sizeof(buffer), stdin);
    BSTree t = BSTreeRead(line1);
    printf("\nTree:\n\n");
    BSTreeShow(t);

    int l;
    if (scanf("%d", &l) != 1) {
        printf("error: failed to read l\n");
        return 1;
    }

    int ans = minDiff(t, l);
    printf("\nminimum difference on level %d: %d\n", l, ans);

    BSTreeFree(t);
}

