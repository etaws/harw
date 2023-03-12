#ifndef HARW_QUEUE_H
#define HARW_QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct queue queue;

queue* queue_create(size_t max_len);
void queue_destroy(queue* q);

size_t queue_len(queue* q);

bool queue_add(queue* q, void* v);
void* queue_delete(queue* q);

#endif // HARW_QUEUE_H
