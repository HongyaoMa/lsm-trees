#ifndef _LSMTREE_H
#define _LSMTREE_H


typedef struct tag_lsmNode lsmNode;

typedef struct tag_lsmTree{
    int* c0;
    int c0_size;
} lsmTree;

/* Initializer */
int lsm_init(lsmTree * tree);

/* Destructor */
int lsm_free(lsmTree * tree);





#endif