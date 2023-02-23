#ifndef HARW_SEEK_TWO_H
#define HARW_SEEK_TWO_H

#include <stdint.h>
#include <stdlib.h>

typedef struct int_tuple int_tuple;

int_tuple* seek_two_count(size_t len, int16_t a[len], int16_t target);

size_t seek_two_tuple_one(int_tuple* t);
size_t seek_two_tuple_two(int_tuple* t);

void seek_two_clear(int_tuple* t);

#endif
