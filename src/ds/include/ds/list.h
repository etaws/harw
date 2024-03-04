#ifndef HARW_LIST_H_
#define HARW_LIST_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct ListNode ListNode;
typedef struct DListNode DListNode;

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

struct ListNode* removeNthFromEnd(struct ListNode* head, int n);

typedef struct dlist dlist;

DListNode* dlist_init();
void dlist_clean(DListNode* dummy);

DListNode* dlist_add_to_first(DListNode* dummy,  int key, int val);
void dlist_move_to_first(DListNode* dummy, DListNode* dnode);

void dlist_delete_tail(DListNode* dummy);

typedef struct LRUCache LRUCache;

LRUCache* lRUCacheCreate(int capacity);
int lRUCacheGet(LRUCache* obj, int key);
void lRUCachePut(LRUCache* obj, int key, int value);
void lRUCacheFree(LRUCache* obj);

#endif
