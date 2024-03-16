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

TEST(tree, tree_11) {

  int a[] = {3, 9, 20, 0, 0, 15, 7};

  TreeNode* root = tree_create(a, sizeof(a) / sizeof(a[0]));

  int level = 0;
  int* returnColumnSizes = 0;
  int** r = levelOrder(root, &level, &returnColumnSizes);
  REQUIRE_EQ(level, 3);

  tree_clean(root);

  for (size_t i = 0; i < level; ++i) {
    for (size_t j = 0; j < returnColumnSizes[i]; ++j) {
      printf("%d ", r[i][j]);
    }
    printf("\n");
  }

  if (r != 0) {
    free(r);
  }

  if (returnColumnSizes != 0) {
    free(returnColumnSizes);
  }
}

TEST(tree, tree_12) {

  int a[] = {3, 1, 4, 0, 2};

  TreeNode* root = tree_create(a, sizeof(a) / sizeof(a[0]));

  int r = kthSmallest(root, 1);
  REQUIRE_EQ(r, 1);

  tree_clean(root);
}

TEST(tree, tree_13) {

  int a[] = {1, 2, 5, 3, 4, 0, 6};

  TreeNode* root = tree_create(a, sizeof(a) / sizeof(a[0]));

  flatten(root);

  tree_clean(root);
}

TEST(tree, tree_14) {

  int preorder[] = {3, 9, 20, 15, 7};

  int inorder[] = {9, 3, 15, 20, 7};

  TreeNode* root = buildTree(preorder, 5, inorder, 5);
}

TEST(tree, tree_15) {

  int a[] = {5, 4, 8, 11, 0, 13, 4, 7, 2, 0, 0, 5, 1};
  TreeNode* root = tree_create(a, sizeof(a) / sizeof(a[0]));

  int r = pathSum(root, 22);

  printf("%d\n", r);
  REQUIRE_EQ(r, 3);

  tree_clean(root);
}