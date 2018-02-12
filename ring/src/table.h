#ifndef TABLE_H
#define TABLE_H

#include <openssl/sha.h>

typedef struct cache {
    int cache_id;
    char *cache_name;
    int replication_factor;
} cache;

int hash(int);

#endif
