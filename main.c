#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list/list.h"

int main(void) {

  printf("begin to test...\n");

  node* n = node_new(0);

  node_delete(n);

  list* l = list_create();
  assert(list_len(l) == 0);

  node* n1 = node_new(1);
  list_insert(l, n1);
  assert(list_len(l) == 1);

  node* n2 = node_new(2);
  list_insert(l, n2);
  assert(list_len(l) == 2);

  list_destroy(l);
  assert(list_len(l) == 0);

  printf("all tests pass.\n");

  return EXIT_SUCCESS;
}
