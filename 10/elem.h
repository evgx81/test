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
typedef struct Elem_Array{
    char *value;
    struct Elem_Array *next;
} Elem_Array;

Elem *elem_new();

void elem_free(Elem *elem);

void elem_parse(char *elem_pack , struct Elem **elem);

void elem_get(struct Elem *elem , const char *key,char **value);

Elem_Iterator* elem_iterator(struct Elem *elem);

char *elem_keys_iterate(struct Elem *elem, struct Elem_Iterator **elem_iterator);

Elem_Array *elem_array_new();

void elem_array_free(Elem_Array *elem_array);

void elem_array_parse(const char *elem_array_pack , struct Elem_Array **elem_array);

void elem_array_pack(struct Elem_Array *elem_array , char **elem_array_pack);

void elem_array_get(struct Elem_Array *elem_array , const int index , char **value);

void elem_array_add(struct Elem_Array **elem_array , const char *value);

void elem_array_set(struct Elem_Array *elem_array , const int index , const char *value);

void elem_array_remove(struct Elem_Array **elem_array , const int index);

int elem_array_length(struct Elem_Array *elem_array);

void swap(char *s1, char*s2);

int stringlength(char *s);

int reverse(char *s);
