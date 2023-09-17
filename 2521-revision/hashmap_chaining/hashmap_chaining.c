#include "HashMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_handler(unordered_map hashmap, int key_hv, struct Value *insert);

// Your TODOS
int string_to_int(char *str){};

// Really basic modulo hashing function:
// Takes in a string called str, and m should be a prime
// number representing bucket_count
int hash(char *str, int m) {}

unordered_map HashMap_new(int n){};

void HashMap_insert(unordered_map hashmap, char *key, char *value){};
char *HashMap_get(unordered_map hashmap, char *key){};

// Frees a HashMap, feel free to change how this works. This should free your
// ENTIRE HashMap. This is entirely optional and if you want to ignore it,
// either edit the Makefile and remove fsanitize, or ignore all the memory leak
// errors.
void HashMap_free(unordered_map hashmap) {}

/**
 * Given Functions, (Try not to change these)
 */

bool is_prime(int n) {
  if (n <= 1)
    return false;
  if (n <= 3)
    return true;
  if (n % 2 == 0 || n % 3 == 0)
    return false;

  for (int i = 5; i * i < n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0)
      return false;
  }
  return true;
}

int next_prime(int n) {
  if (n <= 2)
    return 2;

  while (!is_prime(n)) {
    n++;
  }
  return n;
}

void HashMap_print(unordered_map hashmap) {
  for (int i = 0; i < hashmap->bucket_count; ++i) {
    struct Value *curr = hashmap->buckets[i];
    int f = 0;
    printf("%d: ", i);
    while (curr != NULL) {
      if (f != 0) {
        printf("->%s %s", curr->key, curr->value);
      } else {
        printf("%s %s", curr->key, curr->value);
      }
      curr = curr->next;
      f++;
    }
    printf("\n");
  }
}
