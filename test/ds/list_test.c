#include "ds/dlist.h"
#include "ds/list.h"
#include "tau/tau.h"

TAU_MAIN()

static size_t add_two_ts(size_t al, int a[al], size_t bl, int b[bl], size_t cl,
                         int c[cl]) {

  ListNode* l1 = list_node_create(al, a);
  ListNode* l2 = list_node_create(bl, b);
  ListNode* r = addTwoNumbers(l1, l2);

  size_t len = list_to_array(r, cl, c);

  list_node_clean(l1);
  list_node_clean(l2);
  list_node_clean(r);

  return len;
}

TEST(list, list_1) {

  int a[] = {0};
  int b[] = {0};
  int c[10];

  size_t len = add_two_ts(sizeof(a) / sizeof(a[0]), a, sizeof(b) / sizeof(b[0]),
                          b, sizeof(c) / sizeof(c[0]), c);

  REQUIRE_EQ(len, 1);
  REQUIRE_EQ(c[0], 0);
}

TEST(list, list_2) {

  int a[] = {2, 4, 3};
  int b[] = {5, 6, 4};
  int c[10];

  size_t len = add_two_ts(sizeof(a) / sizeof(a[0]), a, sizeof(b) / sizeof(b[0]),
                          b, sizeof(c) / sizeof(c[0]), c);

  REQUIRE_EQ(len, 3);
  REQUIRE_EQ(c[0], 7);
  REQUIRE_EQ(c[1], 0);
  REQUIRE_EQ(c[2], 8);
}

TEST(list, list_3) {

  int a[] = {9, 9, 9, 9, 9, 9, 9};
  int b[] = {9, 9, 9, 9};
  int c[10000];

  size_t len = add_two_ts(sizeof(a) / sizeof(a[0]), a, sizeof(b) / sizeof(b[0]),
                          b, sizeof(c) / sizeof(c[0]), c);

  REQUIRE_EQ(len, 8);
  REQUIRE_EQ(c[0], 8);
}

TEST(list, list_4) {

  int a[] = {1, 2, 3, 4, 5};
  ListNode* l1 = list_node_create(sizeof(a) / sizeof(a[0]), a);

  ListNode* d = removeNthFromEnd(l1, 2);

  size_t len = list_to_array(d, 4, a);
  REQUIRE_EQ(len, 4);
  REQUIRE_EQ(a[0], 1);
  REQUIRE_EQ(a[1], 2);
  REQUIRE_EQ(a[2], 3);
  REQUIRE_EQ(a[3], 5);

  list_node_clean(l1);
}

TEST(list, list_5) {

  int a[] = {1, 2};
  ListNode* l1 = list_node_create(sizeof(a) / sizeof(a[0]), a);

  ListNode* d = removeNthFromEnd(l1, 2);

  size_t len = list_to_array(d, 2, a);
  REQUIRE_EQ(len, 1);
  REQUIRE_EQ(a[0], 2);

  list_node_clean(l1);
}

TEST(list, list_6) {

  DListNode* dummy = dlist_init();

  dlist_add_to_first(dummy, 8, 1);
  dlist_add_to_first(dummy, 10, 3);
  dlist_add_to_first(dummy, 100, 5);
  dlist_add_to_first(dummy, 20, 7);

  dlist_clean(dummy);
}

TEST(list, list_7) {

  LRUCache* cache = lRUCacheCreate(1);

  int v1 = lRUCacheGet(cache, 1);
  REQUIRE_EQ(v1, -1);

  lRUCachePut(cache, 1, 5);
  v1 = lRUCacheGet(cache, 1);
  REQUIRE_EQ(v1, 5);

  lRUCachePut(cache, 1, 6);
  v1 = lRUCacheGet(cache, 1);
  REQUIRE_EQ(v1, 6);

  lRUCachePut(cache, 2, 9);
  int v2 = lRUCacheGet(cache, 2);
  REQUIRE_EQ(v2, 9);

  v1 = lRUCacheGet(cache, 1);
  REQUIRE_EQ(v1, -1);

  int v3 = lRUCacheGet(cache, 100);
  REQUIRE_EQ(v3, -1);
  lRUCachePut(cache, 100, 72);
  v3 = lRUCacheGet(cache, 100);
  REQUIRE_EQ(v3, 72);

  lRUCacheFree(cache);
}

TEST(list, list_8) {

  LRUCache* cache = lRUCacheCreate(2);

  int v1 = lRUCacheGet(cache, 1);
  REQUIRE_EQ(v1, -1);

  lRUCachePut(cache, 1, 5);
  v1 = lRUCacheGet(cache, 1);
  REQUIRE_EQ(v1, 5);

  lRUCachePut(cache, 1, 6);
  v1 = lRUCacheGet(cache, 1);
  REQUIRE_EQ(v1, 6);

  lRUCachePut(cache, 2, 9);
  int v2 = lRUCacheGet(cache, 2);
  REQUIRE_EQ(v2, 9);

  v1 = lRUCacheGet(cache, 1);
  REQUIRE_EQ(v1, 6);

  int v3 = lRUCacheGet(cache, 100);
  REQUIRE_EQ(v3, -1);
  lRUCachePut(cache, 100, 72);
  v3 = lRUCacheGet(cache, 100);
  REQUIRE_EQ(v3, 72);

  v2 = lRUCacheGet(cache, 2);
  REQUIRE_EQ(v2, -1);

  lRUCacheFree(cache);
}

TEST(list, list_9) {

  int a[] = {5, -1, 9, 4, 7, -188, 6};

  size_t len = sizeof(a) / sizeof(a[0]);

  ListNode* l1 = list_node_create(len, a);

  ListNode* r = sortList(l1);

  size_t list_len = list_to_array(r, len, a);
  REQUIRE_EQ(list_len, len);
  REQUIRE_EQ(a[0], -188);
  REQUIRE_EQ(a[1], -1);
  REQUIRE_EQ(a[2], 4);
  REQUIRE_EQ(a[3], 5);
  REQUIRE_EQ(a[4], 6);
  REQUIRE_EQ(a[5], 7);
  REQUIRE_EQ(a[6], 9);

  list_node_clean(l1);
}

TEST(list, list_10) {

  int a[] = {
      703,  843,  -259, -959, 276,  277,   207,  -125, -845, -637, -731, -927,
      -401, -58,  -63,  588,  -586, 230,   -415, 406,  235,  811,  -55,  -382,
      -843, 943,  656,  504,  822,  -159,  -620, 558,  -452, -529, 199,  -321,
      -905, 716,  113,  -337, 878,  417,   -652, 40,   365,  711,  662,  0,
      637,  598,  469,  759,  173,  418,   421,  -296, 610,  647,  -287, 506,
      -74,  461,  -299, 592,  308,  -247,  275,  -898, 752,  775,  385,  894,
      788,  98,   -53,  270,  622,  -94,   -693, 945,  231,  -690, -706, 761,
      145,  -69,  -404, -493, 106,  -56,   455,  -621, 63,   912,  -279, 212,
      -548, 196,  -628, 312,  905,  -866,  -89,  -245, -966, -334, -919, -264,
      -758, 514,  -865, -613, -993, 617,   324,  846,  -486, -593, -977, -515,
      -238, 466,  474,  -848, 18,   -19,   138,  -867, 931,  484,  479,  -894,
      -478, -863, -926, 983,  -161, 534,   292,  958,  -827, -87,  -475, -331,
      -292, 604,  169,  -188, -354, 733,   254,  -718, -395, 76,   172,  -128,
      556,  -899, -624, -567, 970,  -642,  162,  -747, 963,  -422, 269,  -779,
      -952, 399,  -466, 9,    -752, -224,  648,  -717, 833,  -950, -409, 694,
      -410, -649, 442,  -156, 333,  -574,  -970, -805, 146,  -79,  997,  -301,
      150,  -938, -373, 698,  766,  531,   962,  -794, -698, -339, 451,  -804,
      -795, -350, 681,  673,  285,  555,   130,  665,  -549, -639, -743, -546,
      710,  -499, -177, -703, 675,  -664,  -943, 839,  24,   255,  561,  865,
      -937, -162, 840,  336,  -520, 137,   738,  -587, -732, -310, 570,  634,
      -309, -10,  49,   -33,  -695, -22,   925,  -517, -831, 714,  214,  -990,
      -884, -756, 30,   -118, 42,   -953,  -634, -875, -687, 919,  885,  582,
      -606, -704, -48,  -565, 686,  882,   70,   294,  287,  -796, 218,  684,
      -352, -474, 498,  112,  -913, 376,   -34,  432,  -476, 35,   615,  902,
      281,  825,  653,  938,  -932, -700,  -815, 404,  182,  149,  227,  166,
      299,  863,  244,  67,   443,  374,   -623, 205,  -353, -116, -820, 593,
      271,  -346, 10,   427,  144,  725,   3,    -641, 765,  587,  -770, 732,
      -71,  187,  -457, -204, 344,  918,   959,  864,  400,  974,  -961, 602,
      636,  460,  964,  -792, -8,   757,   -428, 410,  631,  282,  -997, 517,
      633,  -143, -316, -66,  -202, 754,   888,  -923, -383, -720, -307, 485,
      696,  -521, -381, -262, 932,  134,   -676, -406, -400, 392,  78,   375,
      -340, 803,  -849, -603, -127, 107,   459,  533,  672,  -682, 852,  -566,
      -963, 211,  204,  -638, 870,  -838,  989,  -528, -777, -368, -773, 663,
      597,  295,  97,   121,  180,  525,   802,  52,   901,  243,  526,  677,
      16,   926,  724,  -596, -684, 100,   796,  920,  -622, -420, 797,  -503,
      549,  -137, 936,  891,  -886, -242,  -411, 71,   338,  -790, -625, -47,
      -38,  -757, 337,  -631, -808, -488,  248,  -669, 94,   -246, 306,  -467,
      749,  445,  -2,   267,  -194, 85,    347,  691,  627,  -778, 756,  -217,
      387,  792,  -644, -212, 642,  -1000, -371, 967,  92,   -117, 381,  -999,
      -741, 791,  -92,  819,  -735, 152,   523,  715,  -473, -104, -715, -542,
      -979, -871, -179, -165, 726,  -933,  236,  398,  -324, -101, -461, -28,
      -555, -418, 856,  524,  190,  969,   607,  39,   -822, 185,  975,  34,
      569,  542,  -880, -891, -983, -120,  -920, -844, -465, 91,   586,  405,
      651,  157,  200,  50,   883,  910,   -72,  -141, -174, 143,  343,  201,
      -394, 814,  430,  -136, -971, 898,   -283, -280, 942,  -781, 170,  4,
      -560, 927,  -205, -802, 603,  -434,  -147, -110, -890, -629, 321,  799,
      -44,  298,  225,  720,  -191, 499,   -313, 961,  246,  -828, 679,  314,
      929,  342,  -818, 769,  -442, 353,   -819, 222,  649,  -507, -702, -551,
      624,  84,   -888, -229, -791, 301,   -598, -129, -846, 999,  349,  -859,
      395,  186,  87,   128,  318,  256,   456,  871,  867,  -389, -190, -864,
      234,  -481, 536,  -697, 906,  747};
  ListNode* l1 = list_node_create(sizeof(a) / sizeof(a[0]), a);

  ListNode* r = sortList(l1);

  size_t len = list_to_array(r, sizeof(a) / sizeof(a[0]), a);
  REQUIRE_EQ(len, sizeof(a) / sizeof(a[0]));
  REQUIRE_EQ(a[0], -1000);
  REQUIRE_EQ(a[1], -999);
  REQUIRE_EQ(a[2], -997);
  REQUIRE_EQ(a[3], -993);
  REQUIRE_EQ(a[4], -990);

  // -891,-890,-888,-886,
  REQUIRE_EQ(a[32], -891);
  REQUIRE_EQ(a[33], -890);
  REQUIRE_EQ(a[34], -888);
  REQUIRE_EQ(a[35], -886);
}

TEST(tree, list_7) {

  int a[] = {1, 2, 3, 4};
  ListNode* l1 = list_node_create(sizeof(a) / sizeof(a[0]), a);

  ListNode* d = swapPairs(l1);

  size_t len = list_to_array(d, 4, a);
  REQUIRE_EQ(len, 4);
  REQUIRE_EQ(a[0], 2);
  REQUIRE_EQ(a[1], 1);
  REQUIRE_EQ(a[2], 4);
  REQUIRE_EQ(a[3], 3);

  list_node_clean(l1);
}
