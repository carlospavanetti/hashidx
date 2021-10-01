#ifndef HASHIDX_HASHIDX_H_
#define HASHIDX_HASHIDX_H_

typedef struct HashIdxConnection HashIdxConnection;

HashIdxConnection *hashidx_open();

void hashidx_close(HashIdxConnection *db);

void hashidx_write(HashIdxConnection *db, char *key, char *value);

char *latest_segment_content(HashIdxConnection *db);

#endif // HASHIDX_WRITE_TO_DB_H_
