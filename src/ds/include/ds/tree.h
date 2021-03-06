#ifndef HARW_TREE_H_
#define HARW_TREE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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

#endif // HARW_TREE_H_
