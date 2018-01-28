#ifndef TABLE_H
#define TABLE_H

typedef struct cache {
    int cache_id;
    char *cache_name;
    int replication_factor;
    // TODO other data about the cache (IP address...)
} cache;

#endif
