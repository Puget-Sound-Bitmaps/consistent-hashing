#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "table.h"
#include "tree_map.h"

int hash(int key)
{
    const unsigned char* ibuf = (const unsigned char*)&(key);
    unsigned char obuf[256];
    SHA256(ibuf, strlen((const char *)ibuf), obuf);
    int i;
    unsigned long long digest = 0;
    int s = strlen((const char *)obuf);
    for (i = 0; i < s; i++) {
        digest += obuf[i];
    }
    return digest;
}
