#ifndef HARW_TREE_H_
#define HARW_TREE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct TreeNode TreeNode;

TreeNode* tree_create(const int a[], size_t len);
void tree_clean(TreeNode* root);

int* inorder_traversal(struct TreeNode* root, int* returnSize);
int* preorder_traversal(struct TreeNode* root, int* returnSize);
int* postorder_traversal(struct TreeNode* root, int* returnSize);
bool is_symmetric(struct TreeNode* root);
int max_depth(struct TreeNode* root);
bool is_balanced(struct TreeNode* root);
bool isValidBST(struct TreeNode* root);
TreeNode* sortedArrayToBST(int* nums, int numsSize);

typedef struct tree tree;

tree* tree_new(void);
size_t tree_size(tree* t);
size_t tree_height(tree* t);
void tree_reverse(tree* t);

void tree_insert(tree* tree, uint16_t v);
void tree_mid(size_t len, tree* t, uint16_t r[len]);
void tree_pre(size_t len, tree* t, uint16_t r[len]);
void tree_post(size_t len, tree* t, uint16_t r[len]);
void tree_destroy(tree* t);

bool create_mirror_tree();

int** levelOrder(struct TreeNode* root, int* returnSize,
                 int** returnColumnSizes);

int kthSmallest(struct TreeNode* root, int k);

#endif // HARW_TREE_H_
