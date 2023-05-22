#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kson.h"


int main()
{
    char *json_text = "({\"Key_1\":\"Value_1\",\"Key_2\":\"Value_2\"})";

    Kson *kson = kson_new();

    kson_parse(json_text, &kson);

    Kson_Iterator* iterator = kson_iterator(kson);


    char* key1 = kson_keys_iterate(kson, &iterator);

    printf("%s", key1);

    char* val1 = NULL;

    kson_get(kson, key1, &val1);
   
    printf("%s", val1);


    printf("%d", iterator != NULL);


    char* key2 = kson_keys_iterate(kson, &iterator);

    printf("%s", key2);

    char* val2 = NULL;

    kson_get(kson, key2, &val2);
   
    printf("%s", val2);

    return 0;
}