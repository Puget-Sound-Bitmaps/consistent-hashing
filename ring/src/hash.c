#include <math.h>
#include "hash.h"

// Knuth multiplication hash (https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key)
int knuth_mult_hash(int k)
{
    return k * KMH_CST % (int) pow(2.0, sizeof(int));
}
