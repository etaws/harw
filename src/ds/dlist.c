
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "ds/dlist.h"

struct DListNode {
  int key;
  int val;
  struct DListNode* next;
  struct DListNode* pre;
};

#define LRU_MAX_SIZE 10000

struct LRUCache {
  DListNode* dummy;
  int capacity;
  int len;
  DListNode* hash[LRU_MAX_SIZE];
};

DListNode* dlist_init(void) {
  DListNode* dummy = malloc(sizeof(struct DListNode));
  dummy->next = dummy;
  dummy->pre = dummy;
  dummy->val = -1;
  dummy->key = -1;

  return dummy;
}

void dlist_clean(DListNode* dummy) {
  while (dummy->next != dummy) {
    DListNode* t = dummy->next;

    DListNode* pre = t->pre;
    DListNode* next = t->next;

    pre->next = next;
    next->pre = pre;

    free(t);
  }

  free(dummy);
}

void dlist_add_first_node(DListNode* dummy, DListNode* dnode) {

  DListNode* first = dummy->next;

  dummy->next = dnode;

  dnode->pre = dummy;
  dnode->next = first;

  first->pre = dnode;
}

DListNode* dlist_add_to_first(DListNode* dummy, int key, int val) {

  DListNode* dnode = malloc(sizeof(struct DListNode));
  dnode->next = 0;
  dnode->pre = 0;
  dnode->val = val;
  dnode->key = key;

  dlist_add_first_node(dummy, dnode);

  return dnode;
}

void dlist_move_to_first(DListNode* dummy, DListNode* dnode) {
  assert((dnode != dummy) && (dnode->pre != 0));

  if (dnode->pre == dummy) {
    return;
  }

  DListNode* pre = dnode->pre;
  DListNode* next = dnode->next;

  pre->next = next;
  next->pre = pre;

  dlist_add_first_node(dummy, dnode);
}

void dlist_delete_tail(DListNode* dummy) {
  if (dummy->next == dummy) {
    return;
  }

  assert(dummy->pre != 0);

  DListNode* tail = dummy->pre;
  DListNode* pre = tail->pre;
  pre->next = dummy;
  dummy->pre = pre;

  free(tail);
}

LRUCache* lRUCacheCreate(int capacity) {

  LRUCache* cache = malloc(sizeof(LRUCache));

  cache->dummy = dlist_init();

  memset(cache->hash, 0, sizeof(cache->hash));

  cache->capacity = capacity;
  cache->len = 0;

  return cache;
}

void lRUCacheFree(LRUCache* obj) {
  if (obj == 0) {
    return;
  }

  dlist_clean(obj->dummy);
  obj->dummy = 0;
  obj->len = 0;
  obj->capacity = 0;
  free(obj);
}

int lRUCacheGet(LRUCache* obj, int key) {
  if ((key < 0) || (key >= LRU_MAX_SIZE)) {
    return -1;
  }

  if (obj->hash[key] == 0) {
    return -1;
  }

  DListNode* v_node = obj->hash[key];
  int v = v_node->val;
  if (v == -1) {
    return -1;
  }

  dlist_move_to_first(obj->dummy, v_node);

  return v;
}

void lRUCachePut(LRUCache* obj, int key, int value) {

  if ((key < 0) || (key >= LRU_MAX_SIZE)) {
    return;
  }

  if (obj->hash[key] == 0) {
    if (obj->len == obj->capacity) {
      int old_key = obj->dummy->pre->key;
      obj->hash[old_key] = 0;
      dlist_delete_tail(obj->dummy);
      (obj->len)--;
    }
    DListNode* dnode = dlist_add_to_first(obj->dummy, key, value);
    obj->hash[key] = dnode;
    (obj->len)++;
    return;
  }

  DListNode* v_node = obj->hash[key];
  v_node->val = value;
  dlist_move_to_first(obj->dummy, v_node);
}