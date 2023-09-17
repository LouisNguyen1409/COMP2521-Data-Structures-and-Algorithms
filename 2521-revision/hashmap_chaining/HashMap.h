// DO NOT EDIT THESE FILES (Unless you really want to I guess)
#include <stdbool.h>

// Declarations for Hashmap Struct

// forward declaration of value
struct Value;

struct HashMap {
  struct Value **buckets;
  int bucket_count;
};

struct Value {
  char *key;
  char *value;
  struct Value *next;
};

// Lets call the pointer to our HashMap an unordered_map

typedef struct HashMap *unordered_map;

bool is_prime(int n);
int next_prime(int n);

int hash(char *str, int m);

int string_to_int(char *str);

unordered_map HashMap_new(int n);
void HashMap_insert(unordered_map hashmap, char *key, char *value);
char *HashMap_get(unordered_map hashmap, char *key);
void HashMap_print(unordered_map hashmap);
void HashMap_free(unordered_map hashmap);