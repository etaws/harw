#ifndef HARW_TREE_H_
#define HARW_TREE_H_

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

tree* tree_new(void);
size_t tree_size(tree* t);
void tree_insert(tree* tree, uint16_t v);

#endif // HARW_TREE_H_
