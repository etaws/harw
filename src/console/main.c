#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "ds/list.h"
#include "ds/tree.h"

int main(void) {

  printf("begin to test...\n");

  list* l = list_create();
  assert(list_len(l) == 0);

  list_reverse(l);

  list_insert(l, 1);
  assert(list_len(l) == 1);

  list_reverse(l);

  list_insert(l, 2);
  assert(list_len(l) == 2);

  list_reverse(l);

  list_destroy(l);
  assert(list_len(l) == 0);

  tree* t = tree_new();
  tree_destroy(t);

  assert(tree_size(t) == 0);

  uint16_t a[] = {7, 5, 4, 6, 2, 9, 10, 3};

  for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i) {
    tree_insert(t, a[i]);
  }

  assert(tree_size(t) == 8);

  uint16_t b[sizeof(a) / sizeof(uint16_t)] = {0};

  size_t len = tree_size(t);
  tree_post(len, t, b);

  for (int i = 0; i < sizeof(b) / sizeof(b[0]); ++i) {
    printf("%" PRIu32 "\n", b[i]);
  }

  printf("all tests pass.\n");

  tree_destroy(t);

  return EXIT_SUCCESS;
}
