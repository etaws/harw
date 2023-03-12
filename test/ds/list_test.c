#include "ds/list.h"

#include "tau/tau.h"

TAU_MAIN()

TEST(list, list1) {

  int a[] = {1, 3, 4, 5};

  ListNode* head = list_node_create(a, sizeof(a) / sizeof(a[0]));

  list_node_clean(head);
}
