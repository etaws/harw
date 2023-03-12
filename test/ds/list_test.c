#include "ds/tree.h"
#include "tau/tau.h"

TAU_MAIN()

TEST(tree, tree_1) {

  int a[] = {1, 0, 2, 3};

  TreeNode* root = tree_create(a, 4);

  tree_clean(root);
}
