#include "list.h"
#include "tau/tau.h"
#include "tree.h"

TAU_MAIN()

TEST(a, count) {
  node* n = node_new(0);

  node_delete(n);

  list* l = list_create();
  REQUIRE_EQ(list_len(l), 0);

  list_destroy(l);
  REQUIRE_EQ(list_len(l), 0);
}

TEST(b, require) {
  tree* t = tree_new();

  REQUIRE_EQ(tree_size(t), 0);

  uint16_t a[] = {1, 2, 3, 3, 4};

  for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i) {
    tree_insert(t, a[i]);
  }

  REQUIRE_EQ(tree_size(t), 4);
}
