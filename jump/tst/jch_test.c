#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "../src/jump.c"

int test_random(int num_keys, int num_buckets);
int test_sequential(int num_keys, int num_buckets);
int statistics(int num_keys, int num_buckets, int bucket_items[]);

int main(int argc, char* argv[])
{
    /* Default Values */
    int num_keys = 1000;
    int num_buckets = 1000;

    /* First (optional) argument is the number of keys. */
    if (argc > 1) num_keys = strtol(argv[1], NULL, 10);

    /* Second (optional) argument is the number of buckets. */
    if (argc > 2) num_buckets = strtol(argv[2], NULL, 10);

    /* Test hashing random data. */
    int exit_random = test_random(num_keys, num_buckets);

    /* Test hashing sequential data. */
    int exit_sequential = test_sequential(num_keys, num_buckets);

    return exit_random & exit_sequential;
}

int test_random(int num_keys, int num_buckets)
{
    printf("Dividing %i random keys between %i buckets.\n\n", num_keys, num_buckets);

    int bucket_items[num_buckets];
    memset(bucket_items, 0, num_buckets*sizeof(int));

    /* Start keys at random value. */
    srand(time(0));

    for (int key = 0; key < num_keys; ++key)
    {
        int bucket = JumpConsistentHash(rand(), num_buckets);
        ++bucket_items[bucket];
    }

    return statistics(num_keys, num_buckets, bucket_items);
}

int test_sequential(int num_keys, int num_buckets)
{
    printf("Dividing %i sequential keys between %i buckets.\n\n", num_keys, num_buckets);

    int bucket_items[num_buckets];
    memset(bucket_items, 0, num_buckets*sizeof(int));

    /* Start keys at random value. */
    srand(time(0));
    int value = rand();

    for (int key = 0; key < num_keys; ++key)
    {
        int bucket = JumpConsistentHash(value, num_buckets);
        ++bucket_items[bucket];
        ++value;
    }

    return statistics(num_keys, num_buckets, bucket_items);
}

int statistics(int num_keys, int num_buckets, int bucket_items[])
{
    double mean = (double) num_keys / (double) num_buckets;

    double variance = 0.0;
    for ( int i = 0 ; i < num_buckets ; ++i )
    {
        variance += pow((double) bucket_items[i] - mean, 2);
    }
    variance = variance / num_buckets;

    double standard_deviation = sqrt(variance);
    double standard_error = standard_deviation / num_keys;

    printf("Variance: %3.3f\n", variance);
    printf("Standard Deviation: %3.3f\n", standard_deviation);
    printf("Standard Error: %3.3f\n", standard_error);
    printf("\n");

    return EXIT_SUCCESS;
}
