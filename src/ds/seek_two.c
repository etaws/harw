#include "ds/seek_two.h"

#include <stdint.h>
#include <stdlib.h>

struct int_tuple {
  size_t one;
  size_t two;
};

int_tuple* seek_two_count(size_t len, int16_t a[len], int16_t target) {

  int_tuple* r = malloc(sizeof(int_tuple));

  r->one = 0;
  r->two = 0;

  for (size_t i = 0; i < len; ++i) {

    int16_t another = target - a[i];

    for (size_t j = 0; j < len; ++j) {
      if (j == i) {
        continue;
      }

      if (a[j] == another) {

        r->one = i;
        r->two = j;
        return r;
      }
    }
  }

  return r;
}

size_t seek_two_tuple_one(int_tuple* t) { return t->one; }

size_t seek_two_tuple_two(int_tuple* t) { return t->two; }

void seek_two_clear(int_tuple* t) {

  if (t != 0) {
    free(t);
    t = 0;
  }
}
