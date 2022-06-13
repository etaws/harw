#ifndef HARW_LIST_H_
#define HARW_LIST_H_

#include <stddef.h>
#include <stdint.h>

typedef struct list list;

list* list_create(void);
void list_destroy(list* l);

size_t list_len(list* l);

void list_insert(list* l, uint16_t v);

void list_reverse(list* l);

#endif
