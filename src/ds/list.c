#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "ds/list.h"

struct ListNode {
  int val;
  struct ListNode* next;
};

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

typedef struct node node;

struct Node {
  int val;
  struct Node* next;
  struct Node* random;
};

struct node {
  uint16_t v;

  node* next;
};

struct list {
  node* head;
  node* tail;

  size_t len;
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

struct ListNode* delete_duplicates(struct ListNode* head) {

  if (head == 0) {
    return 0;
  }

  struct ListNode* r = head;
  struct ListNode* t = head;

  struct ListNode* c = head;

  while (c->next != 0) {
    c = c->next;
    t->next = 0;

    if (t->val != c->val) {
      t->next = c;
      t = t->next;
    }
  }

  return r;
}

struct ListNode* has_cycle(struct ListNode* head) {

  if (head == 0) {
    return 0;
  }

  if (head->next == 0) {
    return 0;
  }

  struct ListNode* p = head->next;
  struct ListNode* pp = head->next->next;

  while (p != 0) {

    if (p == pp) {
      pp = head;
      break;
    }

    p = p->next;

    if ((pp != 0) && (pp->next != 0) && (pp->next->next != 0)) {
      pp = pp->next->next;
    } else {
      return 0;
    }
  }

  if (p == 0) {
    return 0;
  }

  while (p != pp) {

    p = p->next;
    pp = pp->next;
  }

  return p;
}

struct ListNode* get_intersection_node(struct ListNode* headA,
                                       struct ListNode* headB) {

  if (headA == 0) {
    return 0;
  }

  if (headB == 0) {
    return 0;
  }

  struct ListNode* pa = headA;
  struct ListNode* pb = headB;

  while (pa != pb) {

    if (pa == 0) {
      pa = headB;
    } else {
      pa = pa->next;
    }

    if (pb == 0) {
      pb = headA;
    } else {
      pb = pb->next;
    }
  }

  if (pa != 0) {
    return pa;
  }

  return 0;
}

struct ListNode* reverse_list(struct ListNode* head) {

  if (head == 0 || head->next == 0) {
    return head;
  }

  struct ListNode* r = 0;

  struct ListNode* c = head;
  while (c != 0) {

    struct ListNode* t = c->next;

    c->next = r;
    r = c;

    c = t;
  }

  return r;
}

struct ListNode* reverse_between(struct ListNode* head, int left, int right) {
  if (head == 0 || head->next == 0) {
    return head;
  }

  if (left == right) {
    return head;
  }

  if (head->next->next == 0) {
    struct ListNode* p = head;
    struct ListNode* c = head->next;
    assert(left == 1 && right == 2);
    c->next = p;
    p->next = 0;
    return c;
  }

  struct ListNode* p = 0;
  struct ListNode* c = head;

  struct ListNode* m1 = 0;
  struct ListNode* m2 = 0;

  int i = 0;
  while (c != 0) {
    struct ListNode* t = c->next;
    ++i;

    if (left == i) {
      if (left != 1) {
        m1 = p;
        m2 = c;
      } else {
        m2 = c;
      }
    } else if (i > left && i < right) {
      c->next = p;
    } else if (i == right) {
      if (left != 1) {
        assert(m1 != 0 && m2 != 0);
        m2->next = c->next;
        m1->next = c;
        c->next = p;
        break;
      } else {
        m2->next = c->next;
        head = c;
        c->next = p;
        break;
      }
    }

    p = c;
    c = t;
  }

  return head;
}

bool is_palindrome(struct ListNode* head) {

  if (head == 0 || head->next == 0) {
    return true;
  }

  if (head->next->next == 0) {
    if (head->val == head->next->val) {
      return true;
    } else {
      return false;
    }
  }

  struct ListNode* pre_slow = head;
  struct ListNode* slow = head->next;
  struct ListNode* fast = head->next->next;

  while (fast->next != 0 && fast->next->next != 0) {
    pre_slow = slow;
    slow = slow->next;
    fast = fast->next->next;
  }

  // 奇数
  if (fast->next == 0) {
    pre_slow->next = 0;
    struct ListNode* second_head = slow->next;
    slow->next = 0;
    struct ListNode* second = reverse_list(second_head);

    struct ListNode* c = second;
    struct ListNode* d = head;
    while (c != 0) {

      if (c->val != d->val) {
        return false;
      }

      c = c->next;
      d = d->next;
    }

    return true;
  } else if (fast->next->next == 0) {
    // 偶数
    struct ListNode* second_head = slow->next;
    slow->next = 0;
    struct ListNode* second = reverse_list(second_head);
    struct ListNode* c = second;
    struct ListNode* d = head;
    while (c != 0) {

      if (c->val != d->val) {
        return false;
      }

      c = c->next;
      d = d->next;
    }

    return true;
  }

  return false;
}

struct ListNode* middle_node(struct ListNode* head) {

  if (head == 0 || head->next == 0) {
    return head;
  }

  if (head->next->next == 0) {
    return head->next;
  }

  struct ListNode* slow = head->next;
  struct ListNode* fast = head->next->next;

  while (fast->next != 0 && fast->next->next != 0) {
    slow = slow->next;
    fast = fast->next->next;
  }

  if (fast->next == 0) {
    return slow;
  } else if (fast->next->next == 0) {
    return slow->next;
  }

  return 0;
}

ListNode* list_node_create(size_t len, int a[len]) {

  ListNode* head = 0;
  ListNode* tail = 0;
  for (int i = 0; i < len; ++i) {
    struct ListNode* n = malloc(sizeof(ListNode));
    n->next = 0;
    n->val = a[i];

    if (head == 0) {
      head = n;
      tail = n;
      continue;
    }

    tail->next = n;
    tail = n;
  }

  return head;
}

void list_node_clean(ListNode* head) {
  struct ListNode* c = head;
  while (c != 0) {
    ListNode* t = c;
    c = c->next;
    free(t);
  }
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {

  ListNode* head = 0;
  ListNode* tail = head;

  ListNode* p = l1;
  ListNode* q = l2;
  int up = 0;

  while (p && q) {

    int c = p->val + q->val + up;
    if (c >= 10) {
      up = 1;
    } else {
      up = 0;
    }

    if (head == 0) {
      head = malloc(sizeof(ListNode));
      tail = head;
    } else {
      tail->next = malloc(sizeof(ListNode));
      tail = tail->next;
    }

    tail->next = 0;
    tail->val = c % 10;

    p = p->next;
    q = q->next;
  }

  ListNode* cn = p;
  if (q) {
    cn = q;
  }

  while (cn) {
    int c = cn->val + up;
    if (c >= 10) {
      up = 1;
    } else {
      up = 0;
    }

    if (head == 0) {
      head = malloc(sizeof(ListNode));
      tail = head;
    } else {
      tail->next = malloc(sizeof(ListNode));
      tail = tail->next;
    }

    tail->next = 0;
    tail->val = c % 10;

    cn = cn->next;
  }

  if (up == 1) {
    if (head == 0) {
      head = malloc(sizeof(ListNode));
      tail = head;
    } else {
      tail->next = malloc(sizeof(ListNode));
      tail = tail->next;
    }

    tail->next = 0;
    tail->val = 1;
  }

  return head;
}

size_t list_to_array(ListNode* head, size_t len, int a[len]) {

  ListNode* p = head;

  size_t i = 0;
  while (p) {
    a[i++] = p->val;
    p = p->next;
  }

  return i;
}

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {

  if (head == 0) {
    return 0;
  }

  int i = 0;

  struct ListNode* p = head;
  while (i < (n - 1)) {

    if (p->next == 0) {
      break;
    }

    p = p->next;

    i++;
  }

  if (i < (n - 1)) {
    return 0;
  }

  struct ListNode* pre = head;
  struct ListNode* q = head;
  while (p->next != 0) {
    if (q != head) {
      pre = pre->next;
    }

    q = q->next;
    p = p->next;
  }

  if (q == head) {
    return q->next;
  }

  struct ListNode* r = pre->next;
  pre->next = r->next;

  free(r);

  return head;
}

struct Node* copyRandomList(struct Node* head) {

  if (head == 0) {
    return 0;
  }

  struct Node* p = head;

  while (p != 0) {
    struct Node* copy_it = malloc(sizeof(struct Node));
    copy_it->next = p->next;
    copy_it->random = p->random;
    copy_it->val = p->val;

    p->next = copy_it;

    p = copy_it->next;
  }

  p = head;
  struct Node* q = head->next;
  while (p != 0) {
    if (q->random != 0) {
      q->random = q->random->next;
    }
    if (q->next == 0) {
      break;
    }
    p = q->next;
    q = p->next;
  }

  p = head;
  struct Node* cur = head->next;
  q = cur;
  while (p != 0) {
    p->next = q->next;
    p = q->next;

    if (q->next == 0) {
      break;
    }

    q->next = p->next;
    q = q->next;
  }

  return cur;
}

size_t listNode_len(struct ListNode* head) {
  size_t len = 0;

  struct ListNode* p = head;
  while (p != 0) {
    len++;
    p = p->next;
  }

  return len;
}

struct ListNode* goto_step(struct ListNode* p, size_t step) {
  struct ListNode* q = p;
  size_t l = 0;
  while (l < step) {
    q = q->next;
    l++;
  }

  return q;
}

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
  if (list1 == 0) {
    return list2;
  }

  if (list2 == 0) {
    return list1;
  }

  struct ListNode* p = list1;
  struct ListNode* q = list2;

  struct ListNode* r = 0;
  if (p->val <= q->val) {
    r = p;
    p = p->next;
  } else {
    r = q;
    q = q->next;
  }
  r->next = 0;

  struct ListNode* cur = r;

  while ((p != 0) && (q != 0)) {
    if (p->val <= q->val) {
      cur->next = p;
      p = p->next;
    } else {
      cur->next = q;
      q = q->next;
    }

    cur = cur->next;
    cur->next = 0;
  }

  if (p != 0) {
    cur->next = p;
  }

  if (q != 0) {
    cur->next = q;
  }

  return r;
}

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
  dummy = 0;
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

ListNode* mergeStep(ListNode* p, size_t step) {

  ListNode* pp = p->next;
  ListNode* qq = goto_step(pp, step);

  size_t i = 0;
  size_t j = 0;

  ListNode* c_p = pp;
  ListNode* c_q = qq;
  while ((i < step) && (j < step)) {
    if (c_p->val < c_q->val) {
      p->next = c_p;
      c_p = c_p->next;

      p = p->next;
      p->next = 0;
      i++;
    } else {
      p->next = c_q;
      c_q = c_q->next;

      p = p->next;
      p->next = 0;
      j++;
    }

    if ((c_p == 0) || (c_q == 0)) {
      break;
    }
  }

  if ((i == step) && (j == step)) {
    return c_q;
  } else if (i < step) {
    p->next = c_p;
    i++;
    while (i < step) {
      c_p = c_p->next;
      i++;
    }
    c_p->next = c_q;
    return c_p;
  } else if (j < step) {
    p->next = c_q;
    j++;
    while (j < step) {
      if (p == 0) {
        return 0;
      }
      p = p->next;
      j++;
    }

    if (p == 0) {
      return 0;
    }
    return p->next;
  }

  return 0;
}

struct ListNode* sortList(struct ListNode* head) {
  size_t len = listNode_len(head);
  if ((len == 0) || (len == 1)) {
    return head;
  }

  struct ListNode* dummy = malloc(sizeof(struct ListNode));
  dummy->val = 0;
  dummy->next = head;

  int step = 1;
  while (step * 2 <= len) {
    size_t merge_two = len / (step * 2);

    ListNode* p = dummy;
    for (size_t i = 0; i < merge_two; ++i) {
      p = mergeStep(p, step);
    }

    if (len % (step * 2) > step) {
      mergeStep(p, step);
    }

    step *= 2;
  }

  if (step < len) {
    struct ListNode* q = goto_step(dummy, step);
    struct ListNode* qq = q->next;
    q->next = 0;

    struct ListNode* r = mergeTwoLists(dummy->next, qq);
    free(dummy);
    return r;
  } else {
    struct ListNode* r = dummy->next;
    free(dummy);
    return r;
  }
}
