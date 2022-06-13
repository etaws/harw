#include "list.h"
#include "tau/tau.h"

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
  REQUIRE_LE(1, 1);
  REQUIRE_LE(1, 2);
}
