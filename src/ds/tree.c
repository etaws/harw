#include <assert.h>
#include <stdlib.h>

#include "ds/list.h"
#include "ds/tree.h"

typedef struct data data;

static data* data_new(uint16_t v);

static bool data_mirror(data* d1, data* d2);
static bool data_mirror_v2(data* d1, data* d2, size_t len);
static bool tree_mirror(tree* t);

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
        return false;
      }
      queue_add(q, left->left);
      queue_add(q, right->right);
    }
    if ((left->right != 0) && (right->left != 0)) {
      if (left->right->v != right->left->v) {
        return false;
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
