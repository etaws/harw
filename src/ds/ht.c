// Simple hash table implemented in C.

#include "ds/ht.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Hash table entry (slot may be filled or empty).
typedef struct {
  int32_t key;
  int32_t value;
} ht_entry;

#define INITIAL_CAPACITY 16

// Hash table structure: create with ht_create, free with ht_destroy.
struct ht {
  ht_entry entries[INITIAL_CAPACITY];

  ht_entry black_hole[INITIAL_CAPACITY];

  size_t black_hole_length;
};

// Create hash table and return pointer to it, or NULL if out of memory.
ht* ht_create(void) {
  // Allocate space for hash table struct.
  ht* table = malloc(sizeof(ht));
  if (table == NULL) {
    return NULL;
  }

  table->black_hole_length = 0;

  for (size_t i = 0; i < INITIAL_CAPACITY; ++i) {
    table->entries[i].key = -1;
    table->entries[i].value = -1;

    table->black_hole[i].key = -1;
    table->black_hole[i].value = -1;
  }

  return table;
}

// Free memory allocated for hash table
void ht_destroy(ht* table) { free(table); }

static size_t hash_key(int32_t key) { return key % INITIAL_CAPACITY; }

// Get item with given key from hash table. Return
// value (which was set with ht_set), or -1 if key not found.
int32_t ht_get(ht* table, int32_t key) {
  // AND hash with capacity-1 to ensure it's within entries array.
  size_t hash = hash_key(key);

  assert(hash < INITIAL_CAPACITY);

  if (table->entries[hash].key == -1) {
    return -1;
  }

  if (table->entries[hash].key == key) {
    return table->entries[hash].value;
  }

  for (size_t j = 0; j < table->black_hole_length; ++j) {
    if (table->black_hole[j].key == key) {
      return table->black_hole[j].value;
    }
  }

  return -1;
}

// Set item with given key to value (which must not
// be NULL)；-1 for failed
int32_t ht_set(ht* table, int32_t key, int32_t value) {
  size_t hash = hash_key(key);

  assert(hash < INITIAL_CAPACITY);

  if (table->entries[hash].key == -1) {
    table->entries[hash].key = key;
    table->entries[hash].value = value;
    return (int32_t)hash;
  }

  if (table->black_hole_length < INITIAL_CAPACITY) {
    table->black_hole[table->black_hole_length].key = key;
    table->black_hole[table->black_hole_length].value = value;
    return (int32_t)table->black_hole_length++;
  }

  return -1;
}