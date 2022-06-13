#include <assert.h>
#include <stdlib.h>

#include "tree.h"

static data* data_new(uint16_t v);

data* data_new(uint16_t v) {
  data* d = malloc(sizeof(data));
  d->v = v;
  d->left = 0;
  d->right = 0;

  return d;
}

void tree_insert(tree* tree, uint16_t v) {
  data* d = data_new(v);
  if (tree->root == 0) {
    tree->root = d;
    tree->size += 1;
  }

  data* c = tree->root;
  while (1) {
    if (v < c->v) {
      if (c->left == 0) {
        c->left = d;
        tree->size += 1;
        break;
      } else {
        c = c->left;
      }
    } else if (v > c->v) {
      if (c->right == 0) {
        c->right = d;
        tree->size += 1;
        break;
      } else {
        c = c->right;
      }
    } else {
      break;
    }
  }
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
