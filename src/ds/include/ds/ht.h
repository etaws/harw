// Simple hash table implemented in C.

#ifndef HARW_HT_H_
#define HARW_HT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Hash table structure: create with ht_create, free with ht_destroy.
typedef struct ht ht;

// Create hash table and return pointer to it, or NULL if out of memory.
ht* ht_create(size_t capacity);

// Free memory allocated for hash table, including allocated keys.
void ht_destroy(ht* table);

// Get item with given key from hash table. Return
// value (which was set with ht_set), or -1 if key not found.
void ht_get(ht* table, int32_t key, int32_t* v);

// Set item with given key to value (which must not
// be NULL)；-1 for failed
void ht_set(ht* table, int32_t key, int32_t value);

#endif
