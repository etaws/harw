#ifndef HARW_LIST_H_
#define HARW_LIST_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct ListNode ListNode;

ListNode* list_node_create(int a[], size_t len);
void list_node_clean(ListNode* head);

typedef struct list list;
typedef struct queue queue;

list* list_create(void);
void list_destroy(list* l);

size_t list_len(list* l);

void list_insert(list* l, uint16_t v);

void list_reverse(list* l);

queue* queue_create(size_t max_len);
void queue_destroy(queue* q);

size_t queue_len(queue* q);

bool queue_add(queue* q, void* v);
void* queue_delete(queue* q);

#endif
