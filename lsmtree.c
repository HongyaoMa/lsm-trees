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
    int num_blocks_per_level;
    int max_level_in_ram;

    int c0_size;

} lsmTree;


/* Initializer */
int lsm_init(lsmTree ** treeRef, int input_max_c0_size, int input_num_blocks_per_level, int input_max_level_in_ram){

	// Allocating memory for the tree itself
	(* treeRef) = malloc(sizeof(lsmTree));

    // Parameters for the tree
    (* treeRef) -> num_blocks_per_level = input_num_blocks_per_level;
    (* treeRef) -> max_level_in_ram = input_max_level_in_ram;
    (* treeRef) -> max_c0_size = input_max_c0_size;

    // Allocating memory to the c0 tree
    (* treeRef) -> c0 = malloc(sizeof(lsmNode) * (* treeRef) -> max_c0_size);

    // Meta Data
    (* treeRef) -> c0_size = 0;
    
    return 0;
}

/* Destructor */
int lsm_free(lsmTree ** tree){
    free((*tree) -> c0);
    free(*tree);

    return 0;
}



/********************       Basic Tree Operations ********************/

/* Puting a key value pair into the tree */
int put_with_key(lsmTree * tree, keyType key_to_put, valueType val_to_put){

    tree -> c0[tree->c0_size].key = key_to_put;
    tree -> c0[tree->c0_size].val = val_to_put;
    tree -> c0_size++;

    // TODO: update the tree when c0 is full

    return 0;
}

/* Get the value of a data entry with key_to_get */
/* Returns -1 if the key is not found or is already deleted */

valueType get_with_key(lsmTree * tree, keyType key_to_get){

    int i;

    // Look for the key in the c0 tree
    for (i=0; i < tree-> c0_size; i++){
        if (tree -> c0[i].key == key_to_get){
            return tree -> c0[i].val;
        }
    }

    // If not found: return -1
    return -1;
}


/* Update the value of a data entry with key_to_update */
/* Return original value if the key is found */
/* Returns -1 if the key is not found and a new key is inserted */
valueType update_with_key(lsmTree * tree, keyType key_to_update, valueType val_to_update){

    int i;

    // Look for the key in the c0 tree
    for (i=0; i < tree-> c0_size; i++){
        if (tree -> c0[i].key == key_to_update){
            valueType temp_value = tree -> c0[i].val;
            tree -> c0[i].val = val_to_update;
            return temp_value;
        }
    }

    // If the key is not found: insert it to the tree
    put_with_key(tree, key_to_update, val_to_update);
    return -1;

}


/********************   Meta Data Related  & IO ********************/

/* Get the size of the C0 Tree */
int get_c0_size(lsmTree * tree)
{
	return tree -> c0_size;
}

/* Printing the C0 tree, if the size is smaller than 20 */
int print_c0_tree(lsmTree * tree){

    int i;

    if (tree -> c0_size > 20){
        printf("C0 tree is too bit to print!\n");
        return -1;
    }

    printf("Printing the c0 tree!\n");
    for (i=0; i<tree -> c0_size; i++){
        printf("%d, \t %ld\n",  tree -> c0[i].key,  tree -> c0[i].val);
    }

    return 0;
}



/*********************************************************************/
/************************   Utility Functions ************************/
/*********************************************************************/