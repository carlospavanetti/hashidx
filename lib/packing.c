#include "packing.h"

#include <stdlib.h>
#include <string.h>

char *pack_from_kv(char *key, char *value) {
    size_t key_size = strlen(key);
    size_t value_size = strlen(value);
    size_t pack_size = 2 + key_size + value_size;

    char *pack = (char *) malloc(pack_size + 1);
    pack[0] = (char) key_size;
    memcpy(pack + 1, key, key_size);
    pack[1 + key_size] = (char) value_size;
    memcpy(pack + 2 + key_size, value, value_size);
    pack[pack_size] = '\0';

    return pack;
}
