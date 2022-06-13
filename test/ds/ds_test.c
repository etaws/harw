#include "ds/list.h"
#include "ds/tree.h"
#include "tau/tau.h"

TAU_MAIN()

TEST(a, list) {
  list* l = list_create();
  REQUIRE_EQ(list_len(l), 0);

  list_destroy(l);
  REQUIRE_EQ(list_len(l), 0);
}

TEST(b, tree) {
  tree* t = tree_new();
  tree_destroy(t);

  REQUIRE_EQ(tree_size(t), 0);

  uint16_t a[] = {7, 5, 4, 6, 2, 9, 10, 3};

  for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i) {
    tree_insert(t, a[i]);
  }

  uint16_t b[sizeof(a) / sizeof(u_int16_t)] = {0};

  size_t len = tree_size(t);
  tree_mid(len, t, b);

  uint16_t expect[] = {2, 3, 4, 5, 6, 7, 9, 10};
  for (int i = 0; i < sizeof(expect) / sizeof(expect[0]); ++i) {
    REQUIRE_EQ(expect[i], b[i]);
  }

  uint16_t c[sizeof(a) / sizeof(u_int16_t)] = {0};
  tree_pre(len, t, c);

  uint16_t expect_pre[] = {7, 5, 4, 2, 3, 6, 9, 10};
  for (int i = 0; i < sizeof(expect_pre) / sizeof(expect_pre[0]); ++i) {
    REQUIRE_EQ(expect_pre[i], c[i]);
  }

  uint16_t d[sizeof(a) / sizeof(u_int16_t)] = {0};
  tree_post(len, t, d);

  uint16_t expect_post[] = {3, 2, 4, 6, 5, 10, 9, 7};
  for (int i = 0; i < sizeof(expect_post) / sizeof(expect_post[0]); ++i) {
    REQUIRE_EQ(expect_post[i], d[i]);
  }

  tree_destroy(t);
}

TEST(c, tree_mirror) {
  create_mirror_tree();
  REQUIRE(true);
}
