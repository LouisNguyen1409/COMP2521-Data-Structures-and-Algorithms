
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bstree.h"

static bstree insert_into_bst(bstree t, int item);
void print_bst(bstree t);
bstree bstree_create(int num_elems);
void bstree_free(bstree t);


static bstree insert_into_bst(bstree t, int item) {
    if (t == NULL) {
        bstree nt = malloc(sizeof(*nt));
        nt->value = item;
        nt->left = NULL;
        nt->right = NULL;
        return nt;
    } else {
        if (item < t->value) t->left = insert_into_bst(t->left, item);
        else t->right = insert_into_bst(t->right, item);
        return t;
    }
}

void print_bst(bstree t) {
    if (t != NULL) {
        print_bst(t->left);
        printf("%d ", t->value);
        print_bst(t->right);
    }
}

bstree bstree_create(int num_elems) {
    bstree t = NULL;
    for (int i = 0; i < num_elems; i++) {
        int item;
        scanf("%d", &item);
        t = insert_into_bst(t, item);
    }

    return t;
}


void bstree_free(bstree t) {
    if (t == NULL) return;
    bstree_free(t->right);
    bstree_free(t->left);
    free(t);
}
