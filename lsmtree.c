#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "lsmtree.h"
#include "lsmsubtree.h"


typedef struct tag_lsmTree{
    
    // Parameters 
    int max_c0_size;
    int max_blocks_per_level;
    int max_level_in_ram;
    int level1_multiplier;


    // The c0 tree
    lsmSubTree * c0Tree;
  	
    // Pointers to the trees in memory
    lsmSubTree ** ramTrees;

    // Meta data
    int c0_size;            // current size of the c0 tree
    int total_elements;    
    int * level_sizes;      // the sizes of the blocks in each level
    int * num_blocks;       // the number of blocks in each level

} lsmTree;


/************************   Utility Functions ************************/

/* Update the tree everytime c0 is full*/

int treeUpdate(lsmTree * tree);


/************************  Initializer and Destructor   ************************/
/* Initializer */
int lsmTree_init(lsmTree ** treeRef, int input_max_c0_size, int input_num_blocks_per_level, int input_max_level_in_ram, int input_level1_multiplier){

    int i;

	// Allocating memory for the tree itself
	(* treeRef) = malloc(sizeof(lsmTree));
    if ((* treeRef) == NULL){
        fprintf(stderr, "The LSM Tree failed to initialize! \n");
        return -1;
    }

    // Parameters for the tree
    (* treeRef) -> max_blocks_per_level = input_num_blocks_per_level;
    (* treeRef) -> max_level_in_ram = input_max_level_in_ram;
    (* treeRef) -> max_c0_size = input_max_c0_size;
    (* treeRef) -> level1_multiplier = input_level1_multiplier;

    // Allocating memory to the c0 tree --- c0 tree is not sorted, but we do allocate memory
    if (lsmSubTree_init(&((* treeRef) -> c0Tree), input_max_c0_size, false, true) != 0){
        fprintf(stderr, "Initialization of the c0 tree failed!\n");
        return -1;
    }

    // Meta Data
    (* treeRef) -> c0_size = 0;
    (* treeRef) -> total_elements = 0;
    (* treeRef) -> level_sizes = malloc(sizeof(int) * input_max_level_in_ram);
    (* treeRef) -> num_blocks = malloc(sizeof(int) * input_max_level_in_ram);
    if ((* treeRef) -> level_sizes == NULL || (* treeRef) -> num_blocks == NULL){
        fprintf(stderr, "LSM Tree Meta Data Failed to initialize!\n");
        return -1;
    }

    // Set the number of blocks in each level to be zero, and compute the sizes of each level
    for (i = 0; i < input_max_level_in_ram; i++){
        (* treeRef) -> num_blocks[i] = 0;
        (* treeRef) -> level_sizes[i] = input_max_c0_size * input_level1_multiplier * pow(input_num_blocks_per_level, i);
    }

    // Initialization of the trees in RAM
    (* treeRef) -> ramTrees = malloc(sizeof(lsmSubTree *) * input_num_blocks_per_level * input_max_level_in_ram);
    if ((* treeRef) -> ramTrees == NULL){
        fprintf(stderr, "Pointers to in-memory trees failed to initialize!\n");
        return -1;
    }

    // Set the pointees of the sub-tree pointers to NULL
    for (i=0; i < input_max_level_in_ram * input_num_blocks_per_level; i++){
        (* treeRef) -> ramTrees[i] = NULL;
    }

    return 0;
}

/* Destructor */
int lsmTree_free(lsmTree ** treeRef){

    // Free the c0 tree
    lsmSubTree_free(&((* treeRef) -> c0Tree));

    // Free the in RAM trees
    int i;

    for (i=0; i < (*treeRef) -> max_blocks_per_level *  (*treeRef) -> max_level_in_ram; i++){
        if ((* treeRef) -> ramTrees[i] != NULL){
            lsmSubTree_free((* treeRef) -> ramTrees + i);
        }
    } 

    // Free the pointer to the in RAM trees
    free((*treeRef) -> ramTrees);

    // Other metadata
    free((* treeRef) -> num_blocks);
    free((* treeRef) -> level_sizes);

    // Free the tree itself
    free(*treeRef);

    return 0;
}


/********************     Basic Tree Operations ********************/

/* Puting a key value pair into the tree */
int put_with_key(lsmTree * tree, keyType key_to_put, valueType val_to_put){

    // Put the value into the subtree and increase the size by one
    subTree_put(&(tree->c0Tree), key_to_put, val_to_put); //TODO: catch the abnormal return value

    tree -> c0_size++;
    tree -> total_elements++;

    // Update the tree when c0 is full
    if (tree -> c0_size == tree -> max_c0_size){
        if (treeUpdate(tree)!= 0){
            fprintf(stderr, "Failed to update the tree after putting the key!\n");
            return -1;
        }
    }

    return 0;
}

/* Get the value of a data entry with key_to_get */
/* Returns -1 if the key is not found or is already deleted */

valueType get_with_key(lsmTree * tree, keyType key_to_get)
{
    // First, try getting from the c0 tree:
    valueType retVal = subTree_get(tree -> c0Tree, key_to_get);

    // If the key is found in the c0 tree
    if (retVal  >= 0){
        return retVal;
    }
    // Otherwis: look for the key in the other in ram trees
    else{
        int i_level, i_block;
        for (i_level = 0; i_level < tree -> max_level_in_ram; i_level ++){
            for (i_block = 0; i_block < tree-> num_blocks[i_level]; i_block++){
                retVal = subTree_get(*(tree -> ramTrees + i_block + i_level*tree-> max_blocks_per_level), key_to_get);
                if (retVal >= 0){
                    return retVal;
                }
            }
        }
    }
    // If the key is not in the ram trees either
    return TOMBSTONE;
}

/* Update the value of a data entry with key_to_update */
/* Return original value if the key is found */
/* Returns TOMBSTONE if the key is not found and a new key is inserted */
valueType update_with_key(lsmTree * tree, keyType key_to_update, valueType val_to_update)
{
    // Look for the key from the c0 tree and update
    valueType retVal = subTree_update(&(tree->c0Tree), key_to_update, val_to_update);
    if (retVal >= 0){
        return retVal;
    }
    // Otherwise: look for the key in the other trees in memory
    else{
        int i_level, i_block;
        for (i_level = 0; i_level < tree->max_level_in_ram; i_level++){
            for (i_block = 0; i_block < tree-> num_blocks[i_level]; i_block++){
                retVal = subTree_update((tree -> ramTrees + i_block + i_level*tree-> max_blocks_per_level), key_to_update, val_to_update);
                if (retVal >= 0){
                    return retVal;
                }
            }
        }
    }

    // If not found: put the key-value pair into the tree
    if (put_with_key(tree, key_to_update, val_to_update)!= 0){
        fprintf(stderr, "The key is not found, and putting in the key-value pair failed!\n");
    }
    else{
        // If the key is not in the ram trees either but the put is successful
        return TOMBSTONE;
    }
    return TOMBSTONE;
}

/* Delete a key-value pair from the tree */
valueType delete_with_key(lsmTree * tree, keyType key_to_delete)
{
    // First look for the key in the c0 tree
    valueType retVal = subTree_delete(tree->c0Tree, key_to_delete);
    if (retVal >= 0){
        return retVal;
    }
    // Otherwise: look for the key in the other trees in memory
    else{
        int i_level, i_block;
        for (i_level = 0; i_level < tree->max_level_in_ram; i_level++){
            for (i_block = 0; i_block < tree-> num_blocks[i_level]; i_block++){
                retVal = subTree_delete(*(tree -> ramTrees + i_block + i_level*tree-> max_blocks_per_level), key_to_delete);
                if (retVal >= 0){
                    return retVal;
                }
            }
        }
    }
    // If the key is not found anyway
    return TOMBSTONE;
}

/********************   Meta Data Related  & IO ********************/

/* Get the size of the C0 Tree */
int get_c0_size(lsmTree * tree)
{
    return tree -> c0_size;
}

/* Print the current status of the tree */
int print_tree_param(lsmTree *tree){

    printf("\nPrinting the Parameters of the Tree!\n");

    printf("The maximum size of the C0 level is %d \n", tree->max_c0_size);
    printf("The level 1 blocks are %d times as big as the C0 block\n", tree->level1_multiplier);
    printf("The number of blocks per level is %d \n", tree -> max_blocks_per_level);    
    printf("The number of levels in RAM is %d \n", tree -> max_level_in_ram);

    return 0;
}


/* Print the current status of the tree */
int print_meta_data(lsmTree *tree){

    printf("\nPrinting the Meta Data of the Tree!\n");

    // Size of the c0 tree
    printf("The current size of the C0 tree is %d \n", tree -> c0_size);

    // Total number of elements
    printf("The total number of elements in the tree is %d \n", tree -> total_elements);

    // Number of existing block per level
    int i;
    for (i = 0; i < tree-> max_level_in_ram; i++){
        printf("There are %d blocks in level %d;\n", tree->num_blocks[i], i+1);
    }

    return 0;
}

/* Printing the C0 tree, if the size is smaller than 20 */
int print_c0_tree(lsmTree * tree){
    // Call the subtree print function
    return print_full_subTree(tree->c0Tree);
}


/* Print the full tree in RAM*/
int print_RAM_tree(lsmTree * tree){

    printf("\nPrinting the Full Tree in RAM\n");

    // If the tree is too big to be printed
    if (tree -> max_c0_size > 20){
        printf("The size of the tree is too big to be printed!\n");
        return -1;
    }

    // Print the c0 tree
    printf("\nPrinting the C0 tree:\n");
    print_full_subTree(tree->c0Tree);

    // Print each block in each level of the tree
    int i_level, i_block;
    for(i_level = 0; i_level < tree -> max_level_in_ram; i_level++){
        for (i_block = 0; i_block < tree-> num_blocks[i_level]; i_block++){
            printf("\nPrinting the level %d block %d tree!\n", i_level + 1, i_block + 1);
            print_full_subTree( tree -> ramTrees[i_level * tree -> max_blocks_per_level + i_block]);
        }
    }

    return 0;
}


/*********************************************************************/
/************************   Utility Functions ************************/
/*********************************************************************/

/* Update the tree whenever the c0 tree is full */
int treeUpdate(lsmTree * tree){

    int i_level, i_block;

    // Get the parameters and metadata
    int max_level = tree-> max_level_in_ram;
    int max_blocks = tree-> max_blocks_per_level; 

    
    // Sort the c0 tree w.r.t keys
    subTree_sort(&(tree -> c0Tree));
    

    // If the first level is empty
    if (tree -> num_blocks[0] == 0){

        // move the c0 tree to the first level
        *(tree -> ramTrees) = tree -> c0Tree;

        // make the number of blocks to be one
        tree -> num_blocks[0] = 1;
    }

    // Otherwise: there is at least one block (not necessarily full) in level 1
    else{

        // If the first block is not full
        if (get_subTree_size(*(tree -> ramTrees)) < tree -> level_sizes[0]){

            //Merge the C0 tree and the first block to a temporary tree
            lsmSubTree ** tempTreeRef = malloc(sizeof(lsmSubTree*)); 
            twoWay_subTree_merge(tempTreeRef, &(tree -> c0Tree), tree -> ramTrees);

            // Put the temporary tree into the first block of the 1st level
            *(tree -> ramTrees) = * tempTreeRef;
            free(tempTreeRef);

        }

        // Otherwise: if the first block is full: make space for a new block
        else{
            
            // If the whole first level not full
            if (tree -> num_blocks[0] < max_blocks){

                // Move the later blocks to make space for the 1st block
                for (i_block = tree -> num_blocks[0]; i_block > 0; i_block--){
                    *(tree -> ramTrees + i_block) = *(tree -> ramTrees + i_block -1);
                }

                // move the c0 tree to the first level
                *(tree -> ramTrees) = tree -> c0Tree;

                // make the number of blocks to be one
                tree -> num_blocks[0] ++;
            }

            // Otherwise: the whole first level is completely full: this case should not exist!
            else{
                fprintf(stderr, "\n \n L1 completely full but not merged! This case should not exist!!!\n\n");
            }
        }
    }
    
    // If L1 level is totally full
    if (tree -> num_blocks[0] == max_blocks){
        if (get_subTree_size(*(tree -> ramTrees)) == tree -> level_sizes[0]){

            // Find the first available level
            int empty_level = -1;
            for (i_level = 1; i_level < max_level; i_level++){
                if (tree -> num_blocks[i_level] < max_blocks){
                    empty_level = i_level;
                    break;
                }
            }

            // If there is no empty level, i.e. RAM tree completely full
            if (empty_level < 0){
                fprintf(stderr, "The Whole Tree is Full!\n");
                return -1;
            }
            

            // Get space in the first block in level_available
            for (i_block = tree -> num_blocks[empty_level]; i_block > 0; i_block --){
                *(tree -> ramTrees + empty_level* max_blocks + i_block) = *(tree -> ramTrees+empty_level * max_blocks + i_block -1);
            }
            tree -> num_blocks[empty_level]++;
            

            // Merge all the levels above the empty level
            for (i_level = empty_level - 1; i_level >= 0; i_level --)
            {

                // Merge the trees to the next level
                subTree_merge(tree -> ramTrees + (i_level + 1) * max_blocks, tree -> ramTrees + i_level * max_blocks, max_blocks);

                // Set the number of blocks in this level to be 1
                tree -> num_blocks[i_level] = 1;
            }
            tree -> num_blocks[0] = 0;
        }
    }

    // Re-initialize the c0 tree
    if (lsmSubTree_init(&(tree -> c0Tree), tree -> max_c0_size, false, true) != 0){
        fprintf(stderr, "Re-initialization of the c0 tree failed!\n");
        return -1;
    }
    tree -> c0_size = 0;

    return 0;
}
