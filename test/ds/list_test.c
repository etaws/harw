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
