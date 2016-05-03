#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lsmtree.h"

#define MAX_C0_SIZE 100000


typedef struct tag_lsmNode{
    int key;
    long val;
} lsmNode;


/* Initializer */
int lsm_init(lsmTree * tree){

    // Allocating memory to the c0 tree
    tree -> c0 = malloc(sizeof(lsmNode) * MAX_C0_SIZE);
    tree -> c0_size = 0;
    
}


/* Destructor */
int lsm_free(lsmTree * tree){
    free(tree->c0);
    free(tree);
}
