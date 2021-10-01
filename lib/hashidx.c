#include "hashidx.h"
#include "packing.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEGMENT_SIZE (1 << 12)
struct HashIdxConnection {
    FILE *segment;
};

HashIdxConnection *hashidx_open() {
    HashIdxConnection *db = (HashIdxConnection *) malloc(sizeof(HashIdxConnection));
    db->segment = fmemopen(NULL, SEGMENT_SIZE, "a+");
    return db;
}

void hashidx_close(HashIdxConnection *db) {
    fclose(db->segment);
    free(db);
}

void hashidx_write(HashIdxConnection *db, char *key, char *value) {
    char *pack = pack_from_kv(key, value);
    size_t c = fwrite(pack, sizeof(char), strlen(pack), db->segment);
    free(pack);
}

char *latest_segment_content(HashIdxConnection *db) {
    char *buffer = (char *) malloc(SEGMENT_SIZE);
    rewind(db->segment);
    fread(buffer, sizeof(char), SEGMENT_SIZE, db->segment);
    return buffer;
}
