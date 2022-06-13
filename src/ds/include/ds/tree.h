#ifndef HARW_TREE_H_
#define HARW_TREE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct data data;
typedef struct tree tree;

struct data {
  uint16_t v;

  data* left;
  data* right;
};

struct tree {
  data* root;

  size_t size;
};

data* data_new(uint16_t v);
tree* tree_new(void);
size_t tree_size(tree* t);
bool tree_mirror(tree* t);
void tree_insert(tree* tree, uint16_t v);
void tree_mid(size_t len, tree* t, uint16_t r[len]);
void tree_pre(size_t len, tree* t, uint16_t r[len]);
void tree_post(size_t len, tree* t, uint16_t r[len]);
void tree_destroy(tree* t);

#endif // HARW_TREE_H_
