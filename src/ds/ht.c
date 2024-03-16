// Simple hash table implemented in C.

#include "ds/ht.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct ht_entry ht_entry;

struct ht_entry {
  int32_t key;
  int32_t value;
  ht_entry* next;
};

struct ht {
  ht_entry** entries;

  size_t n;
  size_t capacity;
};

ht* ht_create(size_t capacity) {
  // Allocate space for hash table struct.
  ht* table = malloc(sizeof(ht));
  if (table == 0) {
    return 0;
  }

  table->capacity = capacity;
  table->n = 0;

  table->entries = (ht_entry**)malloc(sizeof(ht_entry*) * capacity);
  memset(table->entries, 0, capacity * sizeof(ht_entry*));

  return table;
}

void ht_destroy(ht* table) {
  for (size_t i = 0; i < table->capacity; ++i) {
    if (table->entries[i] != 0) {
      ht_entry* head = table->entries[i];
      while (head != 0) {
        ht_entry* t = head->next;
        free(head);
        head = t;
      }
    }
  }

  free(table->entries);
  free(table);
}

static size_t hash_key(ht* table, int32_t key) { return key % table->capacity; }

void ht_get(ht* table, int32_t key, int32_t* v) {

  (*v) = 0;

  size_t hash = hash_key(table, key);
  ht_entry* head = table->entries[hash];
  if (head == 0) {
    return;
  }

  while (head != 0) {
    if (head->key == key) {
      (*v) = head->value;
      return;
    }
    head = head->next;
  }
}

void ht_set(ht* table, int32_t key, int32_t value) {
  ht_entry* node = (ht_entry*)malloc(sizeof(ht_entry));
  node->key = key;
  node->value = value;
  node->next = 0;

  size_t hash = hash_key(table, key);
  if (table->entries[hash] == 0) {
    table->entries[hash] = node;
  } else {
    node->next = table->entries[hash];
    table->entries[hash] = node;
  }
}