#include "../src/hash.h"
#include <stdio.h>
#define NUM_TST 100

int main()
{
    int i, v;
    printf("i\th(i)\n---------");
    for (i = 0; i < NUM_TST; i++) {
        v = knuth_mult_hash(i);
        printf("%3d %d\n", i, v);
    }

    return 0;
}
