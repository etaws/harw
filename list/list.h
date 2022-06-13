#ifndef ZZ_LIST_H_
#define ZZ_LIST_H_ 1

#include <stdlib.h>

typedef struct node node;
typedef struct list list;

node *node_new();
void node_delete(node *node);

list *list_create();
void list_insert(list *l, node *n);
size_t list_len(list *l);
void list_destory(list *l);

#endif
