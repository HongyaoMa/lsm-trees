#ifndef _LSMSUBTREE_H
#define _LSMSUBTREE_H

typedef int keyType;
typedef long valueType;

typedef int bool;
#define true 1
#define false 0

// TODO: move into .c file

// The Node
typedef struct tag_lsmNode lsmNode;

// The lsmSubTree
typedef struct tag_lsmSubTree lsmSubTree;


/* Initializer */
int lsmSubTree_init(lsmSubTree ** subTreeRef, int input_maxSize, int isSorted, bool allocMemory);


/* Destructor */
int lsmSubTree_free(lsmSubTree ** subTreeRef);


/************* Basic Subtree Operations **************/

/* Put a key and value pair into the tree */
int subTree_put(lsmSubTree ** subTreeRef, keyType key_to_put, valueType val_to_put);


/* Find the location of a certain key. Return -1 if non-existant */
int subTree_lookup(lsmSubTree *subTree, keyType key_to_lookup);

/* Get the value with a key from the tree */
valueType subTree_get(lsmSubTree * subTree, keyType key_to_get);


/* Update the value for some key in the tree, return old value or -1 */
valueType subTree_update(lsmSubTree ** subTreeRef, keyType key_to_update, valueType val_to_update);


/* Delete a key from the tree, return value or -1*/
valueType subTree_delete(lsmSubTree * subTree, keyType key_to_delete);


/********************   Meta Data Related  & IO ********************/

int get_subTree_size(lsmSubTree * subTree);

int set_subTree_sorted(lsmSubTree ** subTreeRef);

int print_subTree_info(lsmSubTree * subTree);

int print_full_subTree(lsmSubTree * subTree);


/************************* Sorting & Merging **************************/

/* Sorting a subTree using quick sort */
int subTree_sort(lsmSubTree ** subTreeRef);

/* Merging a number of subtrees */
int subTree_merge(lsmSubTree** destRef, lsmSubTree ** subTrees, int num_subTrees);


#endif