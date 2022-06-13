#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct node {
  int v;

  node *next;
};

struct list {
  node *head;
  node *tail;

  size_t len;
};

node *node_new(int v) {
  node *n = malloc(sizeof(node));
  n->v = v;
  n->next = 0;

  return n;
}

void node_delete(node *node) { free(node); }

list *list_create() {
  list *l = malloc(sizeof(list));

  l->head = 0;
  l->tail = 0;
  l->len = 0;

  return l;
}

void list_insert(list *l, node *n) {

  assert(n->next == 0);
  assert(n->v > 0);

  if (l->len == 0) {
    assert(l->head == 0);
    assert(l->tail == 0);

    l->head = n;
    l->tail = n;
    l->len = 1;

    return;
  }

  if (l->len == 1) {
    assert(l->head == l->tail);
  }

  if (l->len >= 1) {
    assert(l->head != 0);
    assert(l->tail != 0);
  }

  assert(l->tail->next == 0);

  l->tail->next = n;
  l->tail = n;
  l->len = l->len + 1;
}

size_t list_len(list *l) {
  assert(l != 0);

  if (l->len == 0) {
    assert(l->head == 0);
    assert(l->tail == 0);
    return 0;
  }

  if (l->len == 1) {
    assert(l->head == l->tail);
    return 1;
  }

  size_t i = 1;
  node *current = l->head;
  while (current->next != l->tail) {
    i++;
    current = current->next;
  }

  i++;
  assert(i == l->len);

  return l->len;
}

void list_destroy(list *l) {
  if (l->head == 0) {
    return;
  }

  node *current = l->head;
  while (current != 0) {
    // if it is the last node, free it, and ALL DONE
    if (current->next == 0) {
      node_delete(current);
      l->head = 0;
      l->tail = 0;
      l->len = 0;
      return;
    }

    node *should_be_freed = current;
    current = current->next;
    free(should_be_freed);
  }
}
