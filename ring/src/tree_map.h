#ifndef TREE_MAP_H
#define TREE_MAP_H

typedef enum {FALSE, TRUE} boolean;
typedef int cache_id;
typedef int hash_value;

// FIXME the above types should be moved to a (globally used) header

typedef enum {RED, BLACK} rbt_node_color; // an alternative to bool

typedef struct node *node_ptr;
typedef struct rbt *rbt_ptr;

typedef struct node
{
    hash_value hv; // key used to identify the node
    cache_id cid;
    rbt_node_color color;
    node_ptr left;
    node_ptr right;
    node_ptr parent;
} node;

typedef struct rbt
{
    node_ptr root;
    node_ptr nil;
    int size;
} rbt;

// RBT initialization functions
rbt_ptr new_rbt(cache_id, hash_value);
node_ptr new_node(rbt_ptr, cache_id, hash_value, rbt_node_color);

// destructors
void free_rbt(rbt_ptr);
void free_node(node_ptr);

// RBT operations (from CLSR)
void left_rotate(rbt_ptr, node_ptr);
void right_rotate(rbt_ptr, node_ptr);
void rbt_insert(rbt_ptr, node_ptr);
void rbt_insert_fixup(rbt_ptr, node_ptr);
void rbt_transplant(rbt_ptr, node_ptr, node_ptr);
node_ptr rbt_min(rbt_ptr, node_ptr);
void rbt_delete(rbt_ptr, node_ptr);
void rbt_delete_fixup(rbt_ptr, node_ptr);

#endif
