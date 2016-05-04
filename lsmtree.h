#ifndef _LSMTREE_H
#define _LSMTREE_H

typedef int keyType;
typedef long valueType;

typedef struct tag_lsmNode lsmNode;
typedef struct tag_lsmTree lsmTree;


/* Initializer */
int lsm_init(lsmTree ** treeRef, int input_max_c0_size, int input_num_blocks_per_level, int input_num_level_in_ram);

/* Destructor */
int lsm_free(lsmTree ** tree);


/********************	Basic Tree Operations ********************/

// TODO
valueType get_with_key(lsmTree * tree, keyType key_to_get);

/* Puting a key value pair into the tree */
int put_with_key(lsmTree * tree, keyType key_to_put, valueType val_to_put);

// TODO
int update_with_key(lsmTree * tree, keyType key_to_update, valueType val_to_update);



/********************	Meta Data Related ********************/

/* Get the size of the C0 Tree */
int get_c0_size(lsmTree * tree);

/* Printing the C0 tree */
int print_c0_tree(lsmTree * tree);


// TODO
/* Print the current status of the tree */
int print_meta_data(lsmTree *tree);



#endif