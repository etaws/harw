#include <assert.h>
#include <stdlib.h>

#include "ds/tree.h"

static data* data_new(uint16_t v);

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
