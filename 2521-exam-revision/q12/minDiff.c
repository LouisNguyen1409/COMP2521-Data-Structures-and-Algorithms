
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

typedef struct item *Item;
struct item {
    int value;
    Item next;
};
static void get_nodes(BSTree t, int level, int l, Item head);
int minDiff(BSTree t, int l) {
    // TODO
    int level = 0;
    Item head = malloc(sizeof(Item));
    head->next = NULL;
    int min = 0;
    get_nodes(t, level, l, head);
    Item curr = head->next;

    while (curr->next != NULL) {
        if (curr->value == head->next->value) {
            min = curr->next->value - curr->value;
        }
        if (curr->next->value - curr->value < min) {
            min = curr->next->value - curr->value;
        }
        curr = curr->next;
    }
    // free
    curr = head;
    while (curr != NULL) {
        Item temp = curr->next;
        free(curr);
        curr = temp;
    }
    return min;
}

static void get_nodes(BSTree t, int level, int l, Item head) {
    if (t == NULL) {
        return;
    }
    if (level + 1 == l) {
        if (t->left != NULL && t->right != NULL) {
            
            Item curr = head;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            Item new_1 = malloc(sizeof(Item));
            Item new_2 = malloc(sizeof(Item));
            curr->next = new_1;
            new_1->value = t->left->key;
            new_1->next = new_2;
            new_2->value = t->right->key;
            new_2->next = NULL;
        } else if ((t->left == NULL && t->right != NULL) || (t->left != NULL && t->right == NULL)) {
            Item curr = head;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            Item new = malloc(sizeof(Item));
            curr->next = new;
            if (t->left != NULL) {
                new->value = t->left->key;
            } else if (t->right != NULL) {
                new->value = t->right->key;
            }
            new->next = NULL;
        }
        return;
    }
    get_nodes(t->left, level + 1, l, head);
    get_nodes(t->right, level + 1, l, head);
}