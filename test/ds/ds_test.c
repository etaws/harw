#include "ds/list.h"
#include "ds/tree.h"
#include "tau/tau.h"

TAU_MAIN()

TEST(a, list) {
  node* n = node_new(0);

  node_delete(n);

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

  REQUIRE_EQ(tree_size(t), 8);

  uint16_t b[sizeof(a) / sizeof(u_int16_t)] = {0};
  tree_mid(t->size, t, b);

  uint16_t expect[] = {2, 3, 4, 5, 6, 7, 9, 10};
  for (int i = 0; i < sizeof(expect) / sizeof(expect[0]); ++i) {
    REQUIRE_EQ(expect[i], b[i]);
  }

  uint16_t c[sizeof(a) / sizeof(u_int16_t)] = {0};
  tree_pre(t->size, t, c);

  uint16_t expect_pre[] = {7, 5, 4, 2, 3, 6, 9, 10};
  for (int i = 0; i < sizeof(expect_pre) / sizeof(expect_pre[0]); ++i) {
    REQUIRE_EQ(expect_pre[i], c[i]);
  }

  uint16_t d[sizeof(a) / sizeof(u_int16_t)] = {0};
  tree_post(t->size, t, d);

  uint16_t expect_post[] = {2, 6, 3, 5, 10, 9, 7};
  for (int i = 0; i < sizeof(expect_post) / sizeof(expect_post[0]); ++i) {
    // REQUIRE_EQ(expect_post[i], d[i]);
  }

  tree_destroy(t);
}

TEST(c, tree_mirror) {
  tree* t = tree_new();

  data* d1 = data_new(1);
  data* d2 = data_new(2);
  data* d3 = data_new(2);
  data* d4 = data_new(3);
  data* d5 = data_new(4);
  data* d6 = data_new(4);
  data* d7 = data_new(3);

  t->root = d1;

  d1->left = d2;
  d1->right = d3;

  d2->left = d4;
  d2->right = d5;

  d3->left = d6;
  d3->right = d7;

  t->size = 7;

  REQUIRE_EQ(t->size, 7);

  free(d1);
  free(d2);
  free(d3);
  free(d4);
  free(d5);
  free(d6);
  free(d7);

  bool b = tree_mirror(t);
  REQUIRE_EQ(b, true);

  t->root = 0;
  t->size = 0;

  tree_destroy(t);
}
