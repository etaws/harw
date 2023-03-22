#ifndef HARW_SEEK_TWO_H
#define HARW_SEEK_TWO_H

#include <stdint.h>
#include <stdlib.h>

typedef struct int_tuple int_tuple;

int_tuple* seek_two_count(size_t len, int32_t a[len], int32_t target);

size_t seek_two_tuple_one(int_tuple* t);
size_t seek_two_tuple_two(int_tuple* t);

void seek_two_clear(int_tuple* t);

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n);

void bubbling_sort(int a[], size_t len);

#endif
