#include "ds/list.h"
#include "ds/queue.h"
#include "ds/seek_two.h"
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

  size_t h = tree_height(t);
  REQUIRE_EQ(h, 5);

  tree_destroy(t);
}

TEST(b, tree_reverse) {

  tree* t = tree_new();

  REQUIRE_EQ(tree_size(t), 0);

  uint16_t a[] = {7, 5, 4, 6, 2, 9, 10, 3};

  for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i) {
    tree_insert(t, a[i]);
  }

  size_t len = tree_size(t);

  REQUIRE_EQ(len, 8);

  tree_reverse(t);

  uint16_t e[sizeof(a) / sizeof(u_int16_t)] = {0};
  uint16_t expect_reverse[] = {7, 5, 4, 2, 3, 6, 9, 10};
  tree_pre(len, t, e);
  for (int i = 0; i < sizeof(expect_reverse) / sizeof(expect_reverse[0]); ++i) {
    REQUIRE_EQ(expect_reverse[i], e[i]);
  }

  tree_destroy(t);
}

TEST(c, tree_mirror) {
  bool b = create_mirror_tree();
  REQUIRE(b);
}

TEST(d, queue_len_1) {

  queue* q = queue_create(1);
  REQUIRE(q != 0);
  REQUIRE_EQ(queue_len(q), 0);

  uint32_t a[2] = {1, 2};
  REQUIRE(queue_add(q, &a[0]));
  REQUIRE_EQ(queue_len(q), 1);

  REQUIRE(!queue_add(q, &a[1]));
  REQUIRE_EQ(queue_len(q), 1);

  uint32_t* qd = queue_delete(q);
  REQUIRE_EQ(queue_len(q), 0);

  REQUIRE(queue_add(q, &a[1]));
  REQUIRE_EQ(queue_len(q), 1);

  uint32_t* qd2 = queue_delete(q);
  REQUIRE_EQ(queue_len(q), 0);

  REQUIRE_EQ(queue_delete(q), 0);
  REQUIRE_EQ(queue_len(q), 0);

  queue_destroy(q);
}

TEST(d, queue_len_2) {

  queue* q = queue_create(2);
  REQUIRE(q != 0);

  REQUIRE_EQ(queue_len(q), 0);

  REQUIRE_EQ(queue_delete(q), 0);

  uint32_t a[2] = {1, 2};

  REQUIRE(queue_add(q, &a[0]));
  REQUIRE_EQ(queue_len(q), 1);

  REQUIRE(queue_add(q, &a[1]));
  REQUIRE_EQ(queue_len(q), 2);

  queue_delete(q);
  REQUIRE_EQ(queue_len(q), 1);

  queue_delete(q);
  REQUIRE_EQ(queue_len(q), 0);

  REQUIRE_EQ(queue_delete(q), 0);

  REQUIRE(queue_add(q, &a[1]));
  REQUIRE_EQ(queue_len(q), 1);

  queue_delete(q);
  REQUIRE_EQ(queue_len(q), 0);

  queue_destroy(q);
}

TEST(e, seek_two_1) {

  int32_t a[] = {4, 6, 7, 5};

  int_tuple* r = seek_two_count(4, a, 12);

  REQUIRE_EQ(seek_two_tuple_one(r), 2);
  REQUIRE_EQ(seek_two_tuple_two(r), 3);

  seek_two_clear(r);
}

TEST(e, seek_two_2) {

  int32_t a[] = {2, 3, 4};

  int_tuple* r = seek_two_count(3, a, 6);

  REQUIRE_EQ(seek_two_tuple_one(r), 0);
  REQUIRE_EQ(seek_two_tuple_two(r), 2);

  seek_two_clear(r);
}

TEST(e, seek_two_3) {

  int32_t a[] = {3, 3};

  int_tuple* r = seek_two_count(2, a, 6);

  REQUIRE_EQ(seek_two_tuple_one(r), 0);
  REQUIRE_EQ(seek_two_tuple_two(r), 1);

  seek_two_clear(r);
}

TEST(e, merge) {

  int a[] = {1, 2, 3, 0, 0, 0};
  int b[] = {2, 5, 6};

  merge(a, 6, 3, b, 3, 3);

  REQUIRE_EQ(a[0], 1);
  REQUIRE_EQ(a[1], 2);
  REQUIRE_EQ(a[2], 2);
  REQUIRE_EQ(a[3], 3);
  REQUIRE_EQ(a[4], 5);
  REQUIRE_EQ(a[5], 6);
}

TEST(e, bubbling_sort) {

  int a[] = {2, 1, 3, 0, 0, 0};

  bubbling_sort(a, sizeof(a) / sizeof(a[0]));

  REQUIRE_EQ(a[0], 0);
  REQUIRE_EQ(a[1], 0);
  REQUIRE_EQ(a[2], 0);
  REQUIRE_EQ(a[3], 1);
  REQUIRE_EQ(a[4], 2);
  REQUIRE_EQ(a[5], 3);
}

TEST(e, quick_sort) {

  int n[] = {5, 1, 26, 37, 61, 11, 15, 19, 59, 48};

  int ret = 0;
  int* a = sortArray(n, sizeof(n) / sizeof(a[0]), &ret);

  // 1, 5, 11, 15, 19, 26, 37, 48, 59, 61
  REQUIRE_EQ(a[0], 1);
  REQUIRE_EQ(a[1], 5);
  REQUIRE_EQ(a[2], 11);
  REQUIRE_EQ(a[3], 15);
  REQUIRE_EQ(a[4], 19);
  REQUIRE_EQ(a[5], 26);
  REQUIRE_EQ(a[6], 37);
  REQUIRE_EQ(a[7], 48);
  REQUIRE_EQ(a[8], 59);
  REQUIRE_EQ(a[9], 61);

  free(a);
}

TEST(e, findKthLargest) {

  int n[] = {99, 99};

  int r = findKthLargest(n, sizeof(n) / sizeof(n[0]), 1);

  REQUIRE_EQ(r, 99);
}

TEST(e, addStrings_0) {

  char* r = addStrings(0, 0);

  bool b = (r == 0);
  REQUIRE(b);
}

TEST(e, addStrings_1) {

  char n1[] = "";
  char n2[] = "";

  char* r = addStrings(n1, n2);
  bool b = (r == 0);
  REQUIRE(b);
}

TEST(e, addStrings_2) {

  char n1[] = {'0', '\0'};
  char n2[] = {'0', '\0'};

  char* r = addStrings(n1, n2);

  REQUIRE(r != 0);

  REQUIRE_EQ(r[0], '0');
  REQUIRE_EQ(r[1], '\0');

  free(r);
}

TEST(e, addStrings_3) {

  char n1[] = "9";
  char n2[] = "99";

  char* r = addStrings(n1, n2);

  REQUIRE(r != 0);

  REQUIRE_EQ(r[0], '1');
  REQUIRE_EQ(r[1], '0');
  REQUIRE_EQ(r[2], '8');
  REQUIRE_EQ(r[3], '\0');

  free(r);
}

TEST(e, addStrings_4) {

  char n1[] = "11";
  char n2[] = "123";

  char* r = addStrings(n1, n2);

  REQUIRE(r != 0);

  REQUIRE_EQ(r[0], '1');
  REQUIRE_EQ(r[1], '3');
  REQUIRE_EQ(r[2], '4');
  REQUIRE_EQ(r[3], '\0');

  free(r);
}

TEST(e, permuteRe) {

  int a[] = {1, 2, 3, 4, 5, 6};

  int* b = malloc(sizeof(int) * 720 * 6);
  memset(b, 0, sizeof(int) * 720);
  int r = permuteRe(a, sizeof(a) / sizeof(a[0]), b);
  REQUIRE_EQ(r, 720);

  free(b);
}
