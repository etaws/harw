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

TEST(tree, list_1) {

  int a[] = {2, 3, 4};

  ListNode* head = list_node_create(sizeof(a) / sizeof(a[0]), a);

  int b[10];
  size_t len = list_to_array(head, sizeof(b) / sizeof(b[0]), b);
  list_node_clean(head);

  REQUIRE_EQ(len, 3);
  REQUIRE_EQ(b[0], 2);
  REQUIRE_EQ(b[1], 3);
  REQUIRE_EQ(b[2], 4);
}
