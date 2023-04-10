#ifndef HARW_LIST_H_
#define HARW_LIST_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct ListNode ListNode;

ListNode* list_node_create(size_t len, int a[len]);
void list_node_clean(ListNode* head);
size_t list_to_array(ListNode* head, size_t len, int a[len]);
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2);

typedef struct list list;

list* list_create(void);
void list_destroy(list* l);

size_t list_len(list* l);

void list_insert(list* l, uint16_t v);

void list_reverse(list* l);

#endif
