#ifndef _LSMTREE_H
#define _LSMTREE_H
#include "global.h"

// typedef struct tag_lsmNode lsmNode;
typedef struct tag_lsmTree lsmTree;


/* Initializer */
int lsmTree_init(lsmTree ** treeRef, int input_max_c0_size, int input_num_blocks_per_level, int input_num_level_in_ram, int input_level1_multiplier);

/* Destructor */
int lsmTree_free(lsmTree ** treeRef);


/********************	Basic Tree Operations ********************/

/* Puting a key value pair into the tree */
int put_with_key(lsmTree * tree, keyType key_to_put, valueType val_to_put);

/* Get the value of a data entry with key_to_get */
valueType get_with_key(lsmTree * tree, keyType key_to_get);

/* Update the value of a data entry with key_to_update */
valueType update_with_key(lsmTree * tree, keyType key_to_update, valueType val_to_update);

/* Delete a key-value pair from the tree */
valueType delete_with_key(lsmTree * tree, keyType key_to_delete);

/******************** I/O and Meta Data Related ********************/

/* Get the size of the C0 Tree */
int get_c0_size(lsmTree * tree);

/* Printing the C0 tree */
int print_tree_param(lsmTree *tree);

/* Print the current status of the tree */
int print_meta_data(lsmTree *tree);

/* Printing the C0 tree */
int print_c0_tree(lsmTree * tree);

/* Print the full tree in RAM*/
int print_RAM_tree(lsmTree * tree);

/* Check the size of the tree matches the total number in the subtrees */
int check_treeSize(lsmTree * tree);

#endif