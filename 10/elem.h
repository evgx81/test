#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct Elem{
    char *key;
    char *value;
    struct Elem *next;
} Elem;
typedef struct Elem_Iterator{
    struct Elem *elem;
} Elem_Iterator;

Elem *elem_new();

void elem_free(Elem *elem);

void elem_parse(char *elem_pack , struct Elem **elem);

void elem_get(struct Elem *elem , const char *key,char **value);

Elem_Iterator* elem_iterator(struct Elem *elem);

char *elem_keys_iterate(struct Elem *elem, struct Elem_Iterator **elem_iterator);
