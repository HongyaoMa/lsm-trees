#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lsmtree.h"




typedef struct tag_lsmNode{
    keyType key;
    valueType val;
} lsmNode;

typedef struct tag_lsmTree{
    lsmNode* c0;
  	int max_c0_size;
    int c0_size;


} lsmTree;

/* Initializer */
int lsm_init(lsmTree ** treeRef, int input_max_c0_size){

	// Allocating memory for the tree itself
	(* treeRef) = malloc(sizeof(lsmTree));
	lsmTree * tree = *treeRef;

    // Allocating memory to the c0 tree
    tree -> max_c0_size = input_max_c0_size;
    tree -> c0 = malloc(sizeof(lsmNode) * tree -> max_c0_size);
    tree -> c0_size = 0;
    
    return 0;
}

/* Destructor */
int lsm_free(lsmTree ** tree){
    free((*tree) -> c0);
    free(*tree);

    return 0;
}


/* Get the size of the C0 Tree */
int get_c0_size(lsmTree * tree)
{
	return tree->c0_size;
}
