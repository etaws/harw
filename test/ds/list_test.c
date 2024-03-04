#include "ds/list.h"
#include "ds/tree.h"
#include "tau/tau.h"

TAU_MAIN()

TEST(tree, tree_1) {

  int a[] = {1, 0, 2, 3};

  TreeNode* root = tree_create(a, sizeof(a) / sizeof(a[0]));

  int r = 0;
  int* ra = inorder_traversal(root, &r);

  REQUIRE_EQ(r, 3);
  REQUIRE_EQ(ra[0], 1);
  REQUIRE_EQ(ra[1], 3);
  REQUIRE_EQ(ra[2], 2);

  free(ra);
  ra = 0;

  tree_clean(root);
}

TEST(tree, tree_2) {

  int a[] = {1, 0, 2, 3};

  TreeNode* root = tree_create(a, sizeof(a) / sizeof(a[0]));

  int r = 0;
  int* ra = preorder_traversal(root, &r);

  REQUIRE_EQ(r, 3);
  REQUIRE_EQ(ra[0], 1);
  REQUIRE_EQ(ra[1], 2);
  REQUIRE_EQ(ra[2], 3);

  free(ra);
  ra = 0;

  tree_clean(root);
}

TEST(tree, tree_3) {

  int a[] = {1, 0, 2, 3};

  TreeNode* root = tree_create(a, sizeof(a) / sizeof(a[0]));

  int r = 0;
  int* ra = postorder_traversal(root, &r);

  REQUIRE_EQ(r, 3);
  REQUIRE_EQ(ra[0], 3);
  REQUIRE_EQ(ra[1], 2);
  REQUIRE_EQ(ra[2], 1);

  free(ra);
  ra = 0;

  tree_clean(root);
}

TEST(tree, tree_4) {

  // int a[] = {1, 2, 2, 0, 3, 0, 3};
  int a[] = {1, 2, 2, 3, 4, 4, 3};

  TreeNode* root = tree_create(a, sizeof(a) / sizeof(a[0]));

  bool ok = is_symmetric(root);

  REQUIRE(ok);

  tree_clean(root);
}

TEST(tree, tree_5) {

  int a[] = {3, 9, 20, 0, 0, 15, 7};

  TreeNode* root = tree_create(a, sizeof(a) / sizeof(a[0]));

  int r = max_depth(root);

  REQUIRE_EQ(r, 3);

  tree_clean(root);
}

TEST(tree, tree_6) {

  int a[] = {1, 2, 2, 3, 3, 0, 0, 4, 4};
  // int a[] = {3, 9, 20, 0, 0, 15, 7};

  TreeNode* root = tree_create(a, sizeof(a) / sizeof(a[0]));

  bool r = is_balanced(root);

  REQUIRE(!r);

  tree_clean(root);
}

TEST(tree, tree_7) {

  int a[] = {2, 2, 2};

  struct TreeNode* root = tree_create(a, sizeof(a) / sizeof(a[0]));

  bool r = isValidBST(root);

  REQUIRE(!r);

  tree_clean(root);
}

static size_t add_two_ts(size_t al, int a[al], size_t bl, int b[bl], size_t cl,
                         int c[cl]) {

  ListNode* l1 = list_node_create(al, a);
  ListNode* l2 = list_node_create(bl, b);
  ListNode* r = addTwoNumbers(l1, l2);

  size_t len = list_to_array(r, cl, c);

  list_node_clean(l1);
  list_node_clean(l2);
  list_node_clean(r);

  return len;
}

TEST(tree, list_1) {

  int a[] = {0};
  int b[] = {0};
  int c[10];

  size_t len = add_two_ts(sizeof(a) / sizeof(a[0]), a, sizeof(b) / sizeof(b[0]),
                          b, sizeof(c) / sizeof(c[0]), c);

  REQUIRE_EQ(len, 1);
  REQUIRE_EQ(c[0], 0);
}

TEST(tree, list_2) {

  int a[] = {2, 4, 3};
  int b[] = {5, 6, 4};
  int c[10];

  size_t len = add_two_ts(sizeof(a) / sizeof(a[0]), a, sizeof(b) / sizeof(b[0]),
                          b, sizeof(c) / sizeof(c[0]), c);

  REQUIRE_EQ(len, 3);
  REQUIRE_EQ(c[0], 7);
  REQUIRE_EQ(c[1], 0);
  REQUIRE_EQ(c[2], 8);
}

TEST(tree, list_3) {

  int a[] = {9, 9, 9, 9, 9, 9, 9};
  int b[] = {9, 9, 9, 9};
  int c[10000];

  size_t len = add_two_ts(sizeof(a) / sizeof(a[0]), a, sizeof(b) / sizeof(b[0]),
                          b, sizeof(c) / sizeof(c[0]), c);

  REQUIRE_EQ(len, 8);
  REQUIRE_EQ(c[0], 8);
}

TEST(tree, list_4) {

  int a[] = {1, 2, 3, 4, 5};
  ListNode* l1 = list_node_create(sizeof(a) / sizeof(a[0]), a);

  ListNode* d = removeNthFromEnd(l1, 2);

  size_t len = list_to_array(d, 4, a);
  REQUIRE_EQ(len, 4);
  REQUIRE_EQ(a[0], 1);
  REQUIRE_EQ(a[1], 2);
  REQUIRE_EQ(a[2], 3);
  REQUIRE_EQ(a[3], 5);

  list_node_clean(l1);
}

TEST(tree, list_5) {

  int a[] = {1, 2};
  ListNode* l1 = list_node_create(sizeof(a) / sizeof(a[0]), a);

  ListNode* d = removeNthFromEnd(l1, 2);

  size_t len = list_to_array(d, 2, a);
  REQUIRE_EQ(len, 1);
  REQUIRE_EQ(a[0], 2);

  list_node_clean(l1);
}

TEST(tree, list_6) {

  DListNode* dummy = dlist_init(7);

  dlist_add_to_first(dummy, 8, 1);
  dlist_add_to_first(dummy, 10, 3);
  dlist_add_to_first(dummy, 100, 5);
  dlist_add_to_first(dummy, 20, 7);

  dlist_clean(dummy);
}

TEST(tree, list_7) {

  LRUCache* cache = lRUCacheCreate(1);

  int v1 = lRUCacheGet(cache, 1);
  REQUIRE_EQ(v1, -1);

  lRUCachePut(cache, 1, 5);
  v1 = lRUCacheGet(cache, 1);
  REQUIRE_EQ(v1, 5);

  lRUCachePut(cache, 1, 6);
  v1 = lRUCacheGet(cache, 1);
  REQUIRE_EQ(v1, 6);

  lRUCachePut(cache, 2, 9);
  int v2 = lRUCacheGet(cache, 2);
  REQUIRE_EQ(v2, 9);

  v1 = lRUCacheGet(cache, 1);
  REQUIRE_EQ(v1, -1);

  lRUCacheFree(cache);
}