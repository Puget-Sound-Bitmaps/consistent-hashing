#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include "table.h"
#include "tree_map.h"
#include "hash.h"
#include <assert.h>

void bst_test(node_ptr c)
{
    int right = c->right->cid;
    assert((c->left->cid < c->cid) && (right > c->cid || right == 0));
    if (c->left->cid != 0)
        bst_test(c->left);
    if (c->right->cid != 0)
        bst_test(c->right);
}

cache_id get_cache(vector_id vid)
{
	//hash_value hvid = hash(vid);
	hash_value hvid = vid; // use id hash for now
}

int main()
{
	FILE *fp;
	fp = fopen("test_file", "r");
	size_t read;
	char *line = NULL;
	int cache_id, dupli;
	uint64_t hash_value;
	rbt_ptr tree = new_rbt(); // first node in the tree.
	node_ptr nodes[20];
	int counter = 0;
	while ((read = getline(&line, &read, fp)) != -1) {
		if (line[0] != '#') {
			cache_id = atoi(strtok(line, " "));
			dupli = atoi(strtok(NULL, " "));
			int i;
			for (i = 0; i < dupli; i++) {
				//hash_value = hash(i + cache_id);
				hash_value = cache_id; // using identity hash function now
				while (hash_value <= NIL_HV) { // NIL_HV is reserved and the hash_value must be positive
					hash_value = hash(hash_value + i + cache_id);
				}
				printf("Inserting new node with id %d, hv = %d\n", cache_id, hash_value);
				node_ptr n = new_node(tree, cache_id, hash_value, RED);
				//printf("adding 2 arr\n");

				nodes[counter++] = n;
				//printf("Beginning insert\n");
				rbt_insert(tree, n);
			}
		}
	}
	bst_test(tree->root);
	//printf("Root:" );
	// test successor function
	int i;
	for (i = 0; i < 17; i++) {
		printf("succ of %d is %d\n", i, succ(tree, i));
	}
	//printf("Successor of 5 is: %d\n", succ(tree, 5));
	// test a few deletes

	int j;
	for (j = 0; j < 7; j++) {
		//printf("Deleteing node %d\n", j);
		rbt_delete(tree, nodes[j]);
	}
	bst_test(tree->root);
	return 0;
}
