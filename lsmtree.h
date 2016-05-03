#ifndef _LSMTREE_H
#define _LSMTREE_H

typedef struct tag_lsmNode {
    int key;
    long val;
} lsmNode;

typedef struct tag_lsmTree {
    int* c0;
} lsmTree;



#endif