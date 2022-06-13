#ifndef HARW_LIST_H_
#define HARW_LIST_H_ 1

#include <stddef.h>
#include <stdint.h>

typedef struct node node;
typedef struct list list;

struct node {
  uint16_t v;

  node* next;
};

struct list {
  node* head;
  node* tail;

  size_t len;
};

node* node_new(uint16_t v);
void node_delete(node* node);

list* list_create(void);
void list_insert(list* l, node* n);
size_t list_len(list* l);
void list_destroy(list* l);

#endif
