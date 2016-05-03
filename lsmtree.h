#ifndef _LSMTREE_H
#define _LSMTREE_H

typedef int keyType;
typedef long valueType;


typedef struct tag_lsmNode lsmNode;

typedef struct tag_lsmTree lsmTree;


/* Initializer */
int lsm_init(lsmTree ** treeRef, int input_max_c0_size);


/* Destructor */
int lsm_free(lsmTree ** tree);


/* Get the size of the C0 Tree */
int get_c0_size(lsmTree * tree);



/********************	TODO ********************/



valueType get_with_key(lsmTree * tree, keyType key_to_get);

int put_with_key(lsmTree * tree, keyType key_to_put, valueType val_to_put);

int update_with_key(lsmTree * tree, keyType key_to_update, valueType val_to_update);


/* Print the current status of the tree */
int print_meta_data(lsmTree *tree);



#endif