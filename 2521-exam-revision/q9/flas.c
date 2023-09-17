
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List flas(List l) {
    int length = 0;
    int max_length = 0;
    List curr = l;
    List pointer = curr;
    List max_pointer = NULL;
    while (curr->next != NULL) {
        if (curr->value < curr->next->value) {
            length += 1;
        } else {
            length = 0;
            pointer = curr->next;
        }
        if (max_length < length) {
            max_length = length;
            max_pointer = pointer;
        }
        curr = curr->next;
    }
    return max_pointer;
}

