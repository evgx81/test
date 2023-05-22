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

    printf("%s, %s", kson_keys_iterate(kson, &iterator), kson_keys_iterate(kson, &iterator));

    return 0;
}
