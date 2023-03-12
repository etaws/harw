#include "ds/list.h"

#include "tau/tau.h"
#include <stdint.h>
#include <stdlib.h>

TAU_MAIN()

TEST(list, list1) {

  int32_t a[] = {1, 3, 4, 5};

  ListNode* head = 0;
  ListNode* tail = 0;
  for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i) {
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

  struct ListNode* c = head;
  size_t j = 0;
  while (c != 0) {
    ListNode* t = c;
    REQUIRE_EQ(c->val, a[j]);
    c = c->next;
    free(t);
    j++;
  }
}
