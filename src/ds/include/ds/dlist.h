#ifndef HARW_D_LIST_H_
#define HARW_D_LIST_H_

typedef struct dlist dlist;

typedef struct DListNode DListNode;

DListNode* dlist_init(void);
void dlist_clean(DListNode* dummy);

DListNode* dlist_add_to_first(DListNode* dummy, int key, int val);
void dlist_move_to_first(DListNode* dummy, DListNode* dnode);

void dlist_delete_tail(DListNode* dummy);

typedef struct LRUCache LRUCache;

LRUCache* lRUCacheCreate(int capacity);
int lRUCacheGet(LRUCache* obj, int key);
void lRUCachePut(LRUCache* obj, int key, int value);
void lRUCacheFree(LRUCache* obj);

#endif