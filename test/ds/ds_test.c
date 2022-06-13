#include "ds/list.h"
#include "ds/tree.h"
#include "tau/tau.h"
#include <stdint.h>

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

TEST(d, queue_empty) {

  queue* q = queue_create(1);
  REQUIRE(q != 0);

  size_t len = queue_len(q);
  REQUIRE(len == 0);

  bool ok = queue_add(q, 1);
  REQUIRE(ok == false);

  uint16_t v = queue_delete(q);
  REQUIRE_EQ(v, 0);

  queue_destroy(q);
}

TEST(d, queue_2) {

  queue* q = queue_create(2);
  REQUIRE(q != 0);

  size_t len = queue_len(q);
  REQUIRE(len == 0);

  uint16_t v = queue_delete(q);
  REQUIRE_EQ(v, 0);

  bool ok = queue_add(q, 1);
  REQUIRE(ok == true);
  REQUIRE_EQ(queue_len(q), 1);

  bool ok2 = queue_add(q, 2);
  REQUIRE(ok2 == false);

  uint16_t v1 = queue_delete(q);
  REQUIRE_EQ(v1, 1);

  len = queue_len(q);
  REQUIRE(len == 0);
  v = queue_delete(q);
  REQUIRE_EQ(v, 0);

  ok = queue_add(q, 2);
  REQUIRE(ok == true);
  REQUIRE_EQ(queue_len(q), 1);

  v1 = queue_delete(q);
  REQUIRE_EQ(v1, 2);

  len = queue_len(q);
  REQUIRE(len == 0);

  queue_destroy(q);
}
