#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "ds/ht.h"
#include "ds/queue.h"
#include "ds/tree.h"

typedef struct data data;

static data* data_new(uint16_t v);

static bool data_mirror(data* d1, data* d2);
static bool data_mirror_v2(data* d1, data* d2, size_t len);
static bool tree_mirror(tree* t);
static size_t data_height(data* d);
static size_t data_height_2(data* d, size_t len);
static void data_reverse(data* d);
static void data_reverse_2(data* d, size_t len);

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

struct data {
  uint16_t v;

  data* left;
  data* right;
};

struct tree {
  data* root;

  size_t size;
};

data* data_new(uint16_t v) {
  data* d = malloc(sizeof(data));
  d->v = v;
  d->left = 0;
  d->right = 0;

  return d;
}

void tree_insert(tree* t, uint16_t v) {

  assert(t != 0);

  data* d = data_new(v);

  if (t->root == 0) {
    t->root = d;
    t->size += 1;
    return;
  }

  data* c = t->root;
  while (1) {
    if (v < c->v) {
      if (c->left == 0) {
        c->left = d;
        t->size += 1;
        break;
      } else {
        c = c->left;
      }
    } else if (v > c->v) {
      if (c->right == 0) {
        c->right = d;
        t->size += 1;
        break;
      } else {
        c = c->right;
      }
    } else {
      break;
    }
  }
}

void tree_destroy(tree* t) {
  if (t == 0) {
    return;
  }

  if (t->size == 0) {
    free(t);
    return;
  }

  if (t->root == 0) {
    free(t);
    return;
  }

  data* r[t->size];
  for (size_t j = 0; j < t->size; ++j) {
    r[j] = 0;
  }

  data* a[t->size];
  for (size_t j = 0; j < t->size; ++j) {
    a[j] = 0;
  }

  size_t i = 0;
  size_t r_i = 0;

  data* current = t->root;
  while (1) {
    while (current != 0) {
      a[i++] = current;
      current = current->left;
    }

    if (i == 0) {
      break;
    }

    i -= 1;
    current = a[i];
    r[r_i++] = current;
    assert(r_i <= t->size);

    current = current->right;
  }

  for (size_t j = 0; j < t->size; ++j) {
    free(r[j]);
    r[j] = 0;
  }

  free(t);
}

tree* tree_new(void) {
  tree* t = malloc(sizeof(tree));
  t->size = 0;
  t->root = 0;

  return t;
}

size_t tree_size(tree* t) {
  assert(t != 0);
  return t->size;
}

size_t tree_height(tree* t) {
  assert(t != 0);

  size_t h1 = data_height(t->root);
  size_t h2 = data_height_2(t->root, t->size + 1);

  assert(h1 == h2);

  return h1;
}

size_t data_height(data* d) {
  size_t h_left = 0;
  size_t h_right = 0;
  if (d->left != 0) {
    h_left = data_height(d->left);
  }
  if (d->right != 0) {
    h_right = data_height(d->right);
  }

  if (h_left > h_right) {
    return h_left + 1;
  }
  return h_right + 1;
}

size_t data_height_2(data* d, size_t len) {

  assert(d != 0);

  queue* q = queue_create(len);
  queue_add(q, d);

  size_t current_size = 1;
  size_t r = 0;
  while (1) {
    if (queue_len(q) == 0) {
      break;
    }

    size_t next_size = 0;
    for (size_t i = 0; i < current_size; ++i) {
      assert(queue_len(q) != 0);
      data* one = queue_delete(q);
      if (one->left != 0) {
        queue_add(q, one->left);
        next_size++;
      }
      if (one->right != 0) {
        queue_add(q, one->right);
        next_size++;
      }
    }
    r++;
    current_size = next_size;
  }

  queue_destroy(q);

  return r;
}

void tree_post(size_t len, tree* t, uint16_t r[len]) {
  if (t == 0) {
    return;
  }

  if (t->size == 0) {
    return;
  }

  if (t->root == 0) {
    return;
  }

  assert(len == t->size);

  data** a = malloc(t->size * sizeof(data*));
  for (size_t j = 0; j < t->size; ++j) {
    a[j] = 0;
  }

  size_t i = 0;
  size_t r_i = 0;

  data* current = t->root;
  data* pre_done = 0;
  while (1) {
    while (current != 0) {
      a[i++] = current;
      current = current->left;
    }

    if (i == 0) {
      break;
    }

    i -= 1;
    current = a[i];

    if (current->right == 0) {
      r[r_i++] = current->v;
      assert(r_i <= len);
      pre_done = current;
      current = 0;
    } else if (current->right == pre_done) {
      r[r_i++] = current->v;
      assert(r_i <= len);
      pre_done = current;
      current = 0;
    } else {
      a[i++] = current;
      pre_done = 0;
      current = current->right;
    }
  }

  free(a);
}

void tree_mid(size_t len, tree* t, uint16_t r[len]) {
  if (t == 0) {
    return;
  }

  if (t->size == 0) {
    return;
  }

  if (t->root == 0) {
    return;
  }

  assert(len == t->size);

  data** a = malloc(t->size * sizeof(data*));
  for (size_t j = 0; j < t->size; ++j) {
    a[j] = 0;
  }

  size_t i = 0;
  size_t r_i = 0;

  data* current = t->root;
  while (1) {
    while (current != 0) {
      a[i++] = current;
      current = current->left;
    }

    if (i == 0) {
      break;
    }

    i -= 1;
    current = a[i];
    r[r_i++] = current->v;
    assert(r_i <= len);

    current = current->right;
  }

  free(a);
}

void tree_pre(size_t len, tree* t, uint16_t r[len]) {
  if (t == 0) {
    return;
  }

  if (t->size == 0) {
    return;
  }

  if (t->root == 0) {
    return;
  }

  assert(len == t->size);

  data** a = malloc(t->size * sizeof(data*));
  for (size_t j = 0; j < t->size; ++j) {
    a[j] = 0;
  }

  size_t i = 0;
  size_t r_i = 0;

  data* current = t->root;
  while (1) {
    while (current != 0) {
      r[r_i++] = current->v;
      assert(r_i <= len);
      a[i++] = current;
      current = current->left;
    }

    if (i == 0) {
      break;
    }

    i -= 1;
    current = a[i];

    current = current->right;
  }

  free(a);
}

bool create_mirror_tree() {
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

  assert(t->size == 7);

  bool b = tree_mirror(t);

  free(d1);
  free(d2);
  free(d3);
  free(d4);
  free(d5);
  free(d6);
  free(d7);

  t->root = 0;
  t->size = 0;

  tree_destroy(t);

  return b;
}

bool tree_mirror(tree* t) {

  assert(t != 0);

  bool r1 = data_mirror(t->root->left, t->root->right);
  bool r2 = data_mirror_v2(t->root->left, t->root->right, t->size);

  assert(r1 == r2);

  return r2;
}

bool data_mirror_v2(data* d1, data* d2, size_t len) {

  if ((d1 == 0) && (d2 == 0)) {
    return true;
  }
  if ((d1 != 0) && (d2 == 0)) {
    return false;
  }
  if ((d1 == 0) && (d2 != 0)) {
    return false;
  }

  queue* q = queue_create(len);

  queue_add(q, d1);
  queue_add(q, d2);

  bool r = false;
  while (1) {
    if (queue_len(q) == 0) {
      r = true;
      break;
    }

    data* left = queue_delete(q);
    data* right = queue_delete(q);

    if ((left->left == 0) && (right->right != 0)) {
      r = false;
      break;
    }
    if ((left->left != 0) && (right->right == 0)) {
      r = false;
      break;
    }
    if ((left->right == 0) && (right->left != 0)) {
      r = false;
      break;
    }
    if ((left->right != 0) && (right->left == 0)) {
      r = false;
      break;
    }

    if ((left->left != 0) && (right->right != 0)) {
      if (left->left->v != right->right->v) {
        r = false;
        break;
      }
      queue_add(q, left->left);
      queue_add(q, right->right);
    }
    if ((left->right != 0) && (right->left != 0)) {
      if (left->right->v != right->left->v) {
        r = false;
        break;
      }
      queue_add(q, left->right);
      queue_add(q, right->left);
    }
  }

  queue_destroy(q);

  return r;
}

bool data_mirror(data* d1, data* d2) {
  if ((d1 == 0) && (d2 == 0)) {
    return true;
  }

  if (d1 == 0 && d2 != 0) {
    return false;
  }

  if (d1 != 0 && d2 == 0) {
    return false;
  }

  if (d1->v != d2->v) {
    return false;
  } else {
    bool b1 = data_mirror(d1->left, d2->right);
    bool b2 = data_mirror(d1->right, d2->left);

    return b1 && b2;
  }
}

void data_reverse_2(data* d, size_t len) {
  assert(d != 0);

  queue* q = queue_create(len + 1);
  queue_add(q, d);

  while (1) {
    if (queue_len(q) == 0) {
      break;
    }

    data* one = queue_delete(q);
    data* left = one->left;
    data* right = one->right;
    if (left != 0) {
      queue_add(q, one->left);
    }
    if (right != 0) {
      queue_add(q, one->right);
    }

    one->left = right;
    one->right = left;
  }

  queue_destroy(q);
}

void data_reverse(data* d) {
  assert(d != 0);
  if (d->left != 0) {
    data_reverse(d->left);
  }
  if (d->right != 0) {
    data_reverse(d->right);
  }

  data* left = d->left;
  data* right = d->right;
  d->left = right;
  d->right = left;
}

void tree_reverse(tree* t) {
  assert(t != 0);
  data_reverse(t->root);

  data_reverse_2(t->root, t->size);
}

int* inorder_traversal(struct TreeNode* root, int* returnSize) {

  size_t max_size = 101;

  int* r = malloc(max_size * sizeof(int));

  TreeNode** a = malloc(max_size * sizeof(TreeNode*));
  for (size_t j = 0; j < max_size; ++j) {
    a[j] = 0;
    r[j] = 0;
  }

  size_t i = 0;
  size_t r_i = 0;
  TreeNode* current = root;

  while (1) {
    while (current != 0) {
      a[i++] = current;
      current = current->left;
    }

    if (i == 0) {
      break;
    }

    i -= 1;
    current = a[i];
    r[r_i++] = current->val;

    current = current->right;
  }

  (*returnSize) = r_i;

  free(a);

  return r;
}

int* preorder_traversal(struct TreeNode* root, int* returnSize) {

  size_t max_size = 101;

  int* r = malloc(max_size * sizeof(int));

  TreeNode** a = malloc(max_size * sizeof(TreeNode*));
  for (size_t j = 0; j < max_size; ++j) {
    a[j] = 0;
    r[j] = 0;
  }

  size_t i = 0;
  size_t r_i = 0;
  TreeNode* current = root;

  while (1) {
    while (current != 0) {
      r[r_i++] = current->val;
      a[i++] = current;
      current = current->left;
    }

    if (i == 0) {
      break;
    }

    i -= 1;
    current = a[i];

    current = current->right;
  }

  (*returnSize) = r_i;

  free(a);

  return r;
}

int* postorder_traversal(struct TreeNode* root, int* returnSize) {
  size_t max_size = 101;

  int* r = malloc(max_size * sizeof(int));

  TreeNode** a = malloc(max_size * sizeof(TreeNode*));
  for (size_t j = 0; j < max_size; ++j) {
    a[j] = 0;
    r[j] = 0;
  }

  size_t i = 0;
  size_t r_i = 0;
  TreeNode* current = root;
  TreeNode* pre_done = 0;

  while (1) {
    while (current != 0) {
      a[i++] = current;
      current = current->left;
    }

    if (i == 0) {
      break;
    }

    i -= 1;
    current = a[i];

    if (current->right == 0) {
      r[r_i++] = current->val;
      pre_done = current;
      current = 0;
    } else if (current->right == pre_done) {
      r[r_i++] = current->val;
      pre_done = current;
      current = 0;
    } else {
      a[i++] = current;
      pre_done = 0;
      current = current->right;
    }
  }

  (*returnSize) = r_i;

  free(a);

  return r;
}

bool is_symmetric(struct TreeNode* root) {

  if (root == 0) {
    return true;
  }

  if ((root->right == 0) && (root->left == 0)) {
    return true;
  }

  if ((root->right == 0) || (root->left == 0)) {
    return false;
  }

  if ((root->right->val != root->left->val)) {
    return false;
  }

  queue* q = queue_create(1000);

  queue_add(q, root->left);
  queue_add(q, root->right);

  bool re = true;
  while (1) {

    if (queue_len(q) == 0) {
      re = true;
      break;
    }

    struct TreeNode* left = queue_delete(q);
    struct TreeNode* right = queue_delete(q);

    if ((left->right == 0) && (right->left != 0)) {
      re = false;
      break;
    }

    if ((left->right != 0) && (right->left == 0)) {
      re = false;
      break;
    }

    if ((left->right != 0) && (right->left != 0) &&
        (left->right->val != right->left->val)) {
      re = false;
      break;
    }

    if ((left->right != 0) && (right->left != 0) &&
        (left->right->val == right->left->val)) {
      queue_add(q, left->right);
      queue_add(q, right->left);
    }

    if ((left->left == 0) && (right->right != 0)) {
      re = false;
      break;
    }

    if ((left->left != 0) && (right->right == 0)) {
      re = false;
      break;
    }

    if ((left->left != 0) && (right->right != 0) &&
        (left->left->val != right->right->val)) {
      re = false;
      break;
    }

    if ((left->left != 0) && (right->right != 0) &&
        (left->left->val == right->right->val)) {
      queue_add(q, left->left);
      queue_add(q, right->right);
    }
  }

  queue_destroy(q);

  return re;
}

TreeNode* tree_create(const int a[], size_t len) {

  if (len < 1) {
    return 0;
  }

  TreeNode* root = malloc(sizeof(TreeNode));
  root->val = a[0];
  root->left = 0;
  root->right = 0;

  if (len == 1) {
    return root;
  }

  queue* q = queue_create(len);
  queue_add(q, root);

  size_t i = 1;
  while (1) {
    TreeNode* one = queue_delete(q);
    if (one == 0) {
      break;
    }
    if (i >= len) {
      break;
    }

    if (a[i] != 0) {
      TreeNode* left = malloc(sizeof(TreeNode));
      left->val = a[i];
      left->left = 0;
      left->right = 0;

      one->left = left;

      queue_add(q, left);
    }

    i++;

    if (i >= len) {
      break;
    }

    if (a[i] != 0) {
      TreeNode* right = malloc(sizeof(TreeNode));
      right->val = a[i];
      right->left = 0;
      right->right = 0;

      one->right = right;

      queue_add(q, right);
    }

    i++;
  }

  queue_destroy(q);

  return root;
}

void tree_clean(TreeNode* root) {

  if (root == 0) {
    return;
  }

  queue* q = queue_create(1000);
  queue_add(q, root);

  while (1) {
    TreeNode* one = queue_delete(q);
    if (one == 0) {
      break;
    }

    if (one->left != 0) {
      queue_add(q, one->left);
    }

    if (one->right != 0) {
      queue_add(q, one->right);
    }

    free(one);
  }

  queue_destroy(q);
}

int max_depth(struct TreeNode* root) {

  if (root == 0) {
    return 0;
  }

  queue* q = queue_create(100);
  queue_add(q, root);
  int current_size = 1;

  size_t r = 0;

  while (1) {
    if (queue_len(q) == 0) {
      break;
    }
    int next_size = 0;
    for (int i = 0; i < current_size; ++i) {
      TreeNode* one = queue_delete(q);
      if (one->right != 0) {
        queue_add(q, one->right);
        next_size++;
      }
      if (one->left != 0) {
        queue_add(q, one->left);
        next_size++;
      }
    }

    current_size = next_size;

    r++;
  }

  queue_destroy(q);
  return r;
}

static bool depth_balanced(struct TreeNode* root, int* depth) {
  if (root == 0) {
    *depth = 0;
    return true;
  }

  int left_depth;
  int right_depth;

  bool left_ok = depth_balanced(root->left, &left_depth);
  bool right_ok = depth_balanced(root->right, &right_depth);

  if (!left_ok || !right_ok) {
    return false;
  }

  int diff = left_depth - right_depth;
  if (diff <= 1 && diff >= -1) {
    if (left_depth > right_depth) {
      (*depth) = left_depth + 1;
    } else {
      (*depth) = right_depth + 1;
    }
    return true;
  } else {
    return false;
  }
}

bool is_balanced(struct TreeNode* root) {
  int depth = 0;
  return depth_balanced(root, &depth);
}

struct TreeNode* mid_tree(int* nums, int left, int right) {

  if (left > right) {
    return 0;
  }

  int mid = (left + right) / 2;

  struct TreeNode* root = malloc(sizeof(TreeNode));
  root->val = nums[mid];
  root->left = mid_tree(nums, left, mid - 1);
  root->right = mid_tree(nums, mid + 1, right);

  return root;
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
  return mid_tree(nums, 0, numsSize - 1);
}

static bool valid_with(struct TreeNode* root, int* min, int* max) {
  if (root == 0) {
    *max = 0;
    *min = 0;
    return true;
  }

  int c = root->val;
  *max = c;
  *min = c;

  if (root->left != 0) {
    int l = 0;
    int r = 0;
    bool is_left = valid_with(root->left, &l, &r);

    if (!is_left) {
      return false;
    }

    if (c <= r) {
      return false;
    }

    *min = l;
  }

  if (root->right != 0) {
    int l = 0;
    int r = 0;
    bool is_right = valid_with(root->right, &l, &r);

    if (!is_right) {
      return false;
    }

    if (c >= l) {
      return false;
    }

    *max = r;
  }

  return true;
}

bool isValidBST(struct TreeNode* root) {
  int max = 0;
  int min = 0;
  return valid_with(root, &min, &max);
}

int** levelOrder(struct TreeNode* root, int* returnSize,
                 int** returnColumnSizes, int** column, int** full) {

  if (root == 0) {
    (*returnSize) = 0;
    return 0;
  }

  queue* q = queue_create(2000);
  queue_add(q, root);
  int current_size = 1;

  int** r = malloc(sizeof(int*) * 2000);

  int* current_out = 0;
  size_t j = 0;
  (*column) = malloc(sizeof(int) * 2000);

  (*full) = malloc(sizeof(int) * 2000);
  int* full_now = (*full);

  while (1) {
    if (queue_len(q) == 0) {
      break;
    }
    int next_size = 0;
    for (int i = 0; i < current_size; ++i) {
      TreeNode* one = queue_delete(q);
      if (current_out == 0) {
        current_out = full_now;
        full_now = full_now + current_size;
      }
      current_out[i] = one->val;
      if (one->left != 0) {
        queue_add(q, one->left);
        next_size++;
      }
      if (one->right != 0) {
        queue_add(q, one->right);
        next_size++;
      }
    }

    r[j] = current_out;
    (*column)[j] = current_size;
    current_out = 0;
    j++;

    current_size = next_size;
  }

  queue_destroy(q);

  (*returnSize) = j;
  (*returnColumnSizes) = (*column);

  return r;
}

int kthSmallest(struct TreeNode* root, int k) {
  if (root == 0) {
    return 0;
  }

  int n = 0;
  int r = 0;

  TreeNode** a = malloc(10000 * sizeof(TreeNode*));
  memset(a, 0, 10000 * sizeof(TreeNode*));
  size_t i = 0;

  TreeNode* current = root;
  while (1) {
    while (current != 0) {
      a[i++] = current;
      current = current->left;
    }

    if (i == 0) {
      break;
    }

    i -= 1;
    current = a[i];
    r++;
    n = current->val;
    if (r == k) {
      free(a);
      return n;
    }
    current = a[i];

    current = current->right;
  }

  free(a);

  return n;
}

int* rightSideView(struct TreeNode* root, int* returnSize) {

  if (root == 0) {
    (*returnSize) = 0;
    return 0;
  }

  int* ra = malloc(101 * sizeof(int));

  queue* q = queue_create(101);
  queue_add(q, root);
  int current_size = 1;

  size_t r = 0;
  int j = 0;

  while (1) {
    if (queue_len(q) == 0) {
      break;
    }
    int next_size = 0;
    for (int i = 0; i < current_size; ++i) {
      TreeNode* one = queue_delete(q);
      if ((i + 1) == current_size) {
        ra[j++] = one->val;
      }
      if (one->left != 0) {
        queue_add(q, one->left);
        next_size++;
      }
      if (one->right != 0) {
        queue_add(q, one->right);
        next_size++;
      }
    }

    current_size = next_size;

    r++;
  }

  queue_destroy(q);

  (*returnSize) = j;
  return ra;
}

void flatten(struct TreeNode* root) {
  if (root == 0) {
    return;
  }

  TreeNode** a = malloc(20001 * sizeof(TreeNode*));
  memset(a, 0, 20001 * sizeof(TreeNode*));

  TreeNode** r = malloc(20001 * sizeof(TreeNode*));
  memset(r, 0, 20001 * sizeof(TreeNode*));

  size_t i = 0;
  size_t r_i = 0;

  TreeNode* current = root;
  while (1) {
    while (current != 0) {
      r[r_i++] = current;
      a[i++] = current;
      current = current->left;
    }

    if (i == 0) {
      break;
    }

    i -= 1;
    current = a[i];

    current = current->right;
  }

  free(a);

  TreeNode* c = root;
  for (size_t j = 1; j < r_i; ++j) {
    c->right = r[j];
    c->left = 0;
    c = c->right;
  }

  free(r);
}

int getInOrderRoot(int root, int* inorder, int left, int right, int h[]) {
  return h[root + 3000];
}

TreeNode* buildTreeRe(int r, int left, int right, int* preorder, int* inorder,
                      int inorderSize, int h[]) {
  if (left > right) {
    return 0;
  }

  int root = preorder[r];

  struct TreeNode* node = malloc(sizeof(TreeNode));
  node->val = root;

  int i = getInOrderRoot(root, inorder, left, right, h);
  int left_len = i - left;
  int right_len = right - i;
  node->left = buildTreeRe(r + 1, left, left + left_len - 1, preorder, inorder,
                           inorderSize, h);
  node->right = buildTreeRe(r + i - left + 1, i + 1, right, preorder, inorder,
                            inorderSize, h);

  return node;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder,
                           int inorderSize) {
  int h[6001];
  for (int i = 0; i < inorderSize; ++i) {
    h[inorder[i] + 3000] = i;
  }
  return buildTreeRe(0, 0, inorderSize - 1, preorder, inorder, inorderSize, h);
}

int pathSumRe(TreeNode* root, int target, int sum, ht* m) {
  if (root == 0) {
    return 0;
  }

  int new_sum = root->val + sum;
  int diff = new_sum - target;

  int r = 0;
  ht_get(m, diff, &r);

  int old = 0;
  ht_get(m, new_sum, &old);
  ht_set(m, new_sum, old + 1);

  int left = pathSumRe(root->left, target, new_sum, m);
  int right = pathSumRe(root->right, target, new_sum, m);

  r = r + left + right;

  int ne = 0;
  ht_get(m, new_sum, &ne);
  ht_set(m, new_sum, ne - 1);

  return r;
}

int pathSum(struct TreeNode* root, int targetSum) {

  ht* m = ht_create(201);

  ht_set(m, 0, 1);

  int r = pathSumRe(root, targetSum, 0, m);

  ht_destroy(m);

  return r;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  if ((root == 0) || (root == p) || (root == q)) {
    return root;
  }

  if (root->val == p->val) {
    return root;
  }

  if (root->val == q->val) {
    return root;
  }

  TreeNode* left = lowestCommonAncestor(root->left, p, q);
  TreeNode* right = lowestCommonAncestor(root->right, p, q);

  if (left == 0) {
    return right;
  }

  if (right == 0) {
    return left;
  }

  return root;
}