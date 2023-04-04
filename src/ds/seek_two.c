#include "ds/seek_two.h"
#include "ds/ht.h"
#include "ds/map.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

struct int_tuple {
  size_t one;
  size_t two;
};

int_tuple* seek_two_count(size_t len, int32_t a[len], int32_t target) {

  int_tuple* r = malloc(sizeof(int_tuple));

  r->one = 0;
  r->two = 0;

  //  ht* map = ht_create();
  hashmap* m = hashmap_create();

  for (size_t i = 0; i < len; ++i) {

    int32_t another = target - a[i];

    uintptr_t v = 0;
    bool exit_it = hashmap_get(m, &another, sizeof(int32_t), &v);
    if (exit_it) {
      if (i < (size_t)v) {
        r->one = i;
        r->two = (size_t)v;
      } else {
        r->one = (size_t)v;
        r->two = i;
      }
      hashmap_free(m);
      return r;
    }

    hashmap_set(m, &a[i], sizeof(int32_t), i);
  }

  hashmap_free(m);

  return r;
}

size_t seek_two_tuple_one(int_tuple* t) { return t->one; }

size_t seek_two_tuple_two(int_tuple* t) { return t->two; }

void seek_two_clear(int_tuple* t) {

  if (t != 0) {
    free(t);
  }
}

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
  int i = m - 1;
  int j = n - 1;

  int k = m + n - 1;

  while ((i >= 0) && (j >= 0)) {
    if (nums1[i] > nums2[j]) {
      nums1[k--] = nums1[i--];
    } else {
      nums1[k--] = nums2[j--];
    }
  }

  while (j >= 0) {
    nums1[k--] = nums2[j--];
  }
}

void bubbling_sort(int a[], size_t len) {

  if (len <= 1) {
    return;
  }

  for (size_t i = len - 1; i >= 1; i--) {
    for (size_t j = 0; j < i; j++) {
      if (a[j] > a[j + 1]) {
        int t = a[j];
        a[j] = a[j + 1];
        a[j + 1] = t;
      }
    }
  }
}

static void q_sort(int a[], size_t left, size_t right);

void q_sort(int a[], size_t left, size_t right) {

  if (left >= right) {
    return;
  }

  size_t i = left;
  size_t j = right + 1;

  size_t len = right - left + 1;
  size_t p = rand() % len + left;
  int v = a[p];
  a[p] = a[left];
  a[left] = v;

  while (1) {
    while (1) {
      i++;
      if ((i == right) || (a[i] >= a[left])) {
        break;
      }
    }

    while (1) {
      j--;
      if ((j == left) || (a[left] >= a[j])) {
        break;
      }
    }

    if (i < j) {
      int t = a[i];
      a[i] = a[j];
      a[j] = t;
    }

    if (i >= j) {
      break;
    }
  }

  int s = a[left];
  a[left] = a[j];
  a[j] = s;

  if ((left + 1) < j) {
    q_sort(a, left, j - 1);
  }
  if ((j + 1) < right) {
    q_sort(a, j + 1, right);
  }
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
  int* r = malloc(sizeof(int) * numsSize);
  *returnSize = numsSize;

  for (size_t k = 0; k < numsSize; ++k) {
    r[k] = nums[k];
  }

  if (numsSize <= 1) {
    return r;
  }

  q_sort(r, 0, numsSize - 1);

  return r;
}

int findKthLargest(int* nums, int numsSize, int k) {
  size_t off = 10000;
  size_t len = 20001;
  int* a = malloc(len * sizeof(int));
  for (int i = 0; i < len; ++i) {
    a[i] = 0;
  }

  for (int j = 0; j < numsSize; ++j) {
    int v = nums[j];
    a[v + off]++;
  }

  int t = 0;
  size_t s = len - 1;
  while (1) {
    t += a[s];

    if (t >= k) {
      free(a);
      return s - off;
    }

    if (s == 0) {
      break;
    }

    s--;
  }

  free(a);

  return 0;
}
