/**
 * Server map implemented as a red-black tree
 * Based on CLRS Chap. 13
 */

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "tree_map.h"


// TODO make new tree with root and return it.

rbt_ptr new_rbt(cache_id root_cache_id, hash_value root_hv)
{
    rbt_ptr r;
    r = (rbt_ptr) malloc(sizeof(struct rbt));
    r->nil = (node_ptr) malloc(sizeof(struct node));
    r->nil->color = BLACK;
    r->root = new_node(r, root_cache_id, root_hv, BLACK);
    r->size = 0;
    return r;
}

node_ptr new_node(rbt_ptr t, cache_id cid, hash_value hv, rbt_node_color color)
{
    node_ptr n;
    n = (node_ptr) malloc(sizeof(struct node));
    n->cid = cid;
    n->hv = hv;
    n->color = color;
    n->parent = t->nil;
    n->left = t->nil;
    n->right = t->nil;
    return n;
}

void left_rotate(rbt_ptr t, node_ptr x)
{
    node_ptr y = x->right;
    x->right = y->left;
    if (y->left != t->nil)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == t->nil)
        t->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void right_rotate(rbt_ptr t, node_ptr y)
{
    node_ptr x = y->left;
    y->left = x->right;
    if (x->right != t->nil)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == t->nil)
        t->root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;
    x->right = y;
    y->parent = x;
}

void rbt_insert(rbt_ptr t, node_ptr z)
{
    printf("Insert\n");
    node_ptr x = t->root;
    node_ptr y = t->nil;
    while (x != t->nil) {
        y = x;
        if (z->hv < x->hv)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == t->nil)
        t->root = z;
    else if (z->hv < y->hv)
        y->left = z;
    else
        y->right = z;
    z->left = t->nil;
    z->right = t->nil;
    z->color = RED;
    rbt_insert_fixup(t, z);
}

void rbt_insert_fixup(rbt_ptr t, node_ptr z)
{
    node_ptr y;
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(t, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(t, z->parent->parent);
            }
        }
        else {
            y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(t, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(t, z->parent->parent);
            }
        }
    }
    t->root->color = BLACK;
}

void rbt_transplant(rbt_ptr t, node_ptr u, node_ptr v)
{
    if (u->parent == t->nil) {
        t->root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else
        u->parent->right = v;
    v->parent = u->parent;
}

node_ptr rbt_min(rbt_ptr t, node_ptr x)
{
    while (x->left != t->nil)
        x = x->left;
    return x;
}

void rbt_delete(rbt_ptr t, node_ptr z)
{
    node_ptr x, y = z;
    rbt_node_color y_orig_col = y->color;
    if (z->left == t->nil) {
        x = z->right;
        rbt_transplant(t, z, z->right);
    }
    else if (z->right == t->nil) {
        x = z->left;
        rbt_transplant(t, z, z->left);
    }
    else {
        y = rbt_min(t, z->right);
        y_orig_col = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            rbt_transplant(t, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbt_transplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_orig_col == BLACK)
        rbt_delete_fixup(t, x);
}

void rbt_delete_fixup(rbt_ptr t, node_ptr x)
{
    node_ptr w;
    while (x != t->root && x->color == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(t, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(t, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(t, x->parent);
                x = t->root;
            }
        }
        else {
            w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(t, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(t, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(t, x->parent);
                x = t->root;
            }
        }
    }
    x->color = BLACK;
}
