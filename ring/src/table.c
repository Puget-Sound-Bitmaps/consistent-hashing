#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "table.h"
#include "tree_map.h"
//#include "hash.h"

int main()
{
	FILE *fp;
	fp = fopen("server_file", "r");
	size_t read;
	char *line = NULL;
	printf("Reading file\n");
	int cache_id, hash_value, dupli;
	rbt_ptr tree = new_rbt(0, 0);
	while ((read = getline(&line, &read, fp)) != -1) {
		if (line[0] != '#') {
			cache_id = atoi(strtok(line, " "));
			dupli = atoi(strtok(NULL, " "));
			int i;
			for (i = 0; i < dupli; i++) {
				hash_value = abs((cache_id + i) << 15); // TODO a better hash function
				printf("Inserting new node with id %d, hv = %d\n", cache_id, hash_value);
				rbt_insert(tree, new_node(tree, cache_id, hash_value, RED));
			}
		}
	}
	return 0;
}
