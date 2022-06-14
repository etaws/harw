#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "ds/list.h"

typedef struct node node;

struct node {
  uint16_t v;

  node* next;
};

struct list {
  node* head;
  node* tail;

  size_t len;
};

struct queue {
  size_t head;
  size_t tail;

  size_t max_len;

  void* v[];
};

static node* node_new(uint16_t v);
static void node_delete(node* node);

node* node_new(uint16_t v) {
  node* n = malloc(sizeof(node));
  n->v = v;
  n->next = 0;

  return n;
}

void node_delete(node* node) { free(node); }

list* list_create(void) {
  list* l = malloc(sizeof(list));

  l->head = 0;
  l->tail = 0;
  l->len = 0;

  return l;
}

void list_insert(list* l, uint16_t v) {

  node* n = node_new(v);

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

size_t list_len(list* l) {
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
  node* current = l->head;
  while (current->next != l->tail) {
    i++;
    current = current->next;
  }

  i++;
  assert(i == l->len);

  return l->len;
}

void list_destroy(list* l) {
  if (l->head == 0) {
    free(l);
    return;
  }

  node* current = l->head;
  while (current != 0) {
    // if it is the last node, free it, and ALL DONE
    if (current->next == 0) {
      assert(current == l->tail);

      node_delete(current);
      l->head = 0;
      l->tail = 0;
      l->len = 0;
      break;
    }

    node* should_be_freed = current;
    current = current->next;
    free(should_be_freed);
  }

  free(l);
}

void list_reverse(list* l) {

  if (l->head == 0) {
    return;
  }

  if (l->len == 1) {
    return;
  }

  node* current = l->head;
  node* next = current->next;
  while (current != l->tail) {
    next->next = current;
    current = next;
  }

  node* head = l->head;
  head->next = 0;
  l->head = l->tail;
  l->tail = head;
}

queue* queue_create(size_t max_len) {

  assert(max_len > 0);

  queue* q = malloc(sizeof(queue) + (max_len + 1) * sizeof(void*));
  q->head = 0;
  q->tail = 0;
  q->max_len = max_len + 1;

  return q;
}

void queue_destroy(queue*restrict q) {

  q->head = 0;
  q->tail = 0;
  q->max_len = 0;

  free(q);
}

size_t queue_len(queue*restrict q) {
  if (q->head == q->tail) {
    return 0;
  }

  if (q->tail > q->head) {
    return q->tail - q->head;
  } else {
    return (q->tail) + (q->max_len - q->head);
  }
}

bool queue_add(queue*restrict q, void*restrict v) {
  assert(q != 0);
  assert(v != 0);

  if (queue_len(q) == (q->max_len - 1)) {
    return false;
  }

  q->v[q->tail] = v;

  if (q->tail >= q->max_len - 1) {
    q->tail = 0;
  } else {
    q->tail++;
  }

  return true;
}

void* queue_delete(queue*restrict q) {

  if (queue_len(q) <= 0) {
    return 0;
  }

  void* v = q->v[q->head];

  if (q->head >= q->max_len - 1) {
    q->head = 0;
  } else {
    q->head++;
  }

  return v;
}
