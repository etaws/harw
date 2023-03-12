#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "ds/queue.h"

struct queue {
  size_t head;
  size_t tail;

  size_t max_len;

  void* v[];
};

queue* queue_create(size_t max_len) {

  assert(max_len > 0);

  queue* q = malloc(sizeof(queue) + (max_len + 1) * sizeof(void*));
  q->head = 0;
  q->tail = 0;
  q->max_len = max_len + 1;

  return q;
}

void queue_destroy(queue* restrict q) {

  q->head = 0;
  q->tail = 0;
  q->max_len = 0;

  free(q);
}

size_t queue_len(queue* restrict q) {
  if (q->head == q->tail) {
    return 0;
  }

  if (q->tail > q->head) {
    return q->tail - q->head;
  } else {
    return (q->tail) + (q->max_len - q->head);
  }
}

bool queue_add(queue* restrict q, void* restrict v) {
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

void* queue_delete(queue* restrict q) {

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
