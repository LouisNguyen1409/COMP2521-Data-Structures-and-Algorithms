#include "HashMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void input_handler();
int main() {
  input_handler();

  return 0;
}

void input_handler() {
  int n, s;
  char ch;
  scanf(" %d %d", &n, &s);
  while ((ch = getchar()) != EOF && ch != '\n')
    ;
  unordered_map new = HashMap_new(n);
  for (int i = 0; i < s; ++i) {
    // We don't really care about memory leaks here.
    char *key = calloc(100, sizeof(char));
    char *value = calloc(100, sizeof(char));
    fgets(key, 100, stdin);
    fgets(value, 100, stdin);
    key[strcspn(key, "\n")] = 0;
    value[strcspn(value, "\n")] = 0;
    HashMap_insert(new, key, value);
  }

  HashMap_print(new);

  HashMap_free(new);
}
