#include <stdint.h>

static const uint64_t jch_seed = 2862933555777941757;

int32_t JumpConsistentHash (uint64_t key, int32_t num_buckets)
{
    int64_t b = -1;
    int64_t j = 0;

    double divisor;
    double dividend;

    while (j < num_buckets) {
        b = j;
        key = key * jch_seed + 1;
        divisor = (double)(1LL << 31);
        dividend = (double)((key >> 33) + 1);
        j = (b + 1) * (divisor / dividend);
    }
    return b;
}
