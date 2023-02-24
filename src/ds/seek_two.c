#include "ds/seek_two.h"
#include "ds/ht.h"

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

  ht* map = ht_create();

  for (size_t i = 0; i < len; ++i) {

    int32_t another = target - a[i];

    int32_t v = ht_get(map, another);
    if (v != -1) {
      if (i < (size_t)v) {
        r->one = i;
        r->two = (size_t)v;
      } else {
        r->one = (size_t)v;
        r->two = i;
      }
      ht_destroy(map);
      return r;
    }

    int32_t set_ok = ht_set(map, a[i], (int32_t)i);
    assert(set_ok >= 0);
  }

  ht_destroy(map);

  return r;
}

size_t seek_two_tuple_one(int_tuple* t) { return t->one; }

size_t seek_two_tuple_two(int_tuple* t) { return t->two; }

void seek_two_clear(int_tuple* t) {

  if (t != 0) {
    free(t);
  }
}
