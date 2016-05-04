#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "lsmtree.h"


// Maximum levels for the quick sort function
#define QS_MAX_LEVELS 1000


typedef struct tag_lsmNode{
    keyType key;
    valueType val;
} lsmNode;


typedef struct tag_lsmTree{
    
    // Parameters 
    int max_c0_size;
    int num_blocks_per_level;
    int max_level_in_ram;

    // The c0 tree
    lsmNode* c0Tree;
  	
    // Pointers to the trees in memory
    lsmNode ** ramTrees;

    // Meta data
    int c0_size;            // current size of the c0 tree
    bool * flag_ramTrees;   // the existence of each in RAM tree

    int empty_ram_level;
    int empty_ram_block;

} lsmTree;


/************************   Utility Functions ************************/

/* Update the tree everytime c0 is full*/
int treeUpdate(lsmTree * tree);


/* In-place implementation of Quick Sort for node arrays*/
int quickSort(lsmNode * inputArray, int array_size);

/* Merge two sorted arrays */
lsmNode* sortedMerge(lsmNode ** source1Ref, int size1, lsmNode ** source2Ref, int size2);


/************************  Initializer and Destructor   ************************/
/* Initializer */
int lsm_init(lsmTree ** treeRef, int input_max_c0_size, int input_num_blocks_per_level, int input_max_level_in_ram){

    int i;

	// Allocating memory for the tree itself
	(* treeRef) = malloc(sizeof(lsmTree));

    // Parameters for the tree
    (* treeRef) -> num_blocks_per_level = input_num_blocks_per_level;
    (* treeRef) -> max_level_in_ram = input_max_level_in_ram;
    (* treeRef) -> max_c0_size = input_max_c0_size;

    // Allocating memory to the c0 tree
    (* treeRef) -> c0Tree = malloc(sizeof(lsmNode) * input_max_c0_size);

    // Allocating memory to the pointers to the in RAM trees, and set them all to NULL
    (* treeRef) -> ramTrees = malloc(sizeof(lsmNode *) * input_num_blocks_per_level * input_max_level_in_ram);

    for (i=0; i < input_num_blocks_per_level * input_max_level_in_ram; i++){
        (* treeRef) -> ramTrees[i] = NULL;
    }  

    // Meta Data
    (* treeRef) -> c0_size = 0;
    (* treeRef) -> empty_ram_level = 0;
    (* treeRef) -> empty_ram_block = 0;

    (* treeRef) -> flag_ramTrees = malloc(sizeof(bool) * input_num_blocks_per_level * input_max_level_in_ram);

    for (i=0; i < input_num_blocks_per_level * input_max_level_in_ram; i++){
        (* treeRef) -> flag_ramTrees[i] = 0;
    }  
    
    return 0;
}

/* Destructor */
int lsm_free(lsmTree ** treeRef){

    // Free the c0 tree
    free((*treeRef) -> c0Tree);

    // Free the in RAM trees
    int i;
    for (i=0; i < (*treeRef) -> num_blocks_per_level *  (*treeRef) -> max_level_in_ram; i++){
        if ((* treeRef) -> ramTrees[i] != NULL){
            free((* treeRef) -> ramTrees[i]);
        }
    } 

    // Free the pointer to the in RAM trees
    free((*treeRef) -> ramTrees);

    // Free the flags of the existence of the in RAM trees
    free((* treeRef) -> flag_ramTrees);

    // Free the tree itself
    free(*treeRef);

    return 0;
}


/********************       Basic Tree Operations ********************/

/* Puting a key value pair into the tree */
int put_with_key(lsmTree * tree, keyType key_to_put, valueType val_to_put){

    tree -> c0Tree[tree->c0_size].key = key_to_put;
    tree -> c0Tree[tree->c0_size].val = val_to_put;
    tree -> c0_size++;

    // Update the tree when c0 is full
    if (tree -> c0_size == tree -> max_c0_size){
        treeUpdate(tree);
    }

    return 0;
}

/* Get the value of a data entry with key_to_get */
/* Returns -1 if the key is not found or is already deleted */

valueType get_with_key(lsmTree * tree, keyType key_to_get){

    int i;

    // Look for the key in the c0 tree
    for (i=0; i < tree-> c0_size; i++){
        if (tree -> c0Tree[i].key == key_to_get){
            return tree -> c0Tree[i].val;
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
        if (tree -> c0Tree[i].key == key_to_update){
            valueType temp_value = tree -> c0Tree[i].val;
            tree -> c0Tree[i].val = val_to_update;
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

/* Print the current status of the tree */
int print_meta_data(lsmTree *tree){

/*    // Parameters 
    int max_c0_size;
    int num_blocks_per_level;
    int max_level_in_ram;

    // The c0 tree
    lsmNode* c0Tree;
    
    // Pointers to the trees in memory
    lsmNode ** ramTrees;

    // Meta data
    int c0_size;            // current size of the c0 tree
    bool * flag_ramTrees;   // the existence of each in RAM tree

    int empty_ram_level;
    int empty_ram_block;
    */

    printf("\nPrinting the Meta Data of the Tree!\n");

    printf("\nThe current size of the C0 tree is %d \n", tree->c0_size);

    printf("\nFlas of the in-RAM trees:\n");

    int i_level, i_block;

    for (i_level = 0; i_level < tree -> max_level_in_ram; i_level++)
        for (i_block = 0; i_block < tree -> num_blocks_per_level; i_block ++)
            printf("Existence of the level %d, block %d tree: %d \n", i_level, i_block, tree-> flag_ramTrees[i_level * tree -> num_blocks_per_level + i_block]);

    printf("\nThe first empty level is %d \n", tree-> empty_ram_level);
    printf("\nThe first empty block in the empty level is %d \n", tree-> empty_ram_block);

    return 0;
}

/* Printing the C0 tree, if the size is smaller than 20 */
int print_c0_tree(lsmTree * tree){

    int i;

    if (tree -> c0_size > 20){
        printf("C0 tree is too bit to print!\n");
        return -1;
    }

    if (tree -> c0_size == 0){
        printf("Printing the C0 tree, which is empty!!\n");
        return -1;
    }

    printf("Printing the c0 tree!\n");
    for (i=0; i<tree -> c0_size; i++){
        printf("%d, \t %ld\n",  tree -> c0Tree[i].key,  tree -> c0Tree[i].val);
    }

    return 0;
}


/*********************************************************************/
/************************   Utility Functions ************************/
/*********************************************************************/

/* Update the tree whenever the c0 tree is full */
int treeUpdate(lsmTree * tree){

    if (tree->c0_size < tree -> max_c0_size){
        printf("C0 tree is not full! No need to update the tree!\n"); //TODO: convert to error message?
        return -1;
    }

    // Sort the c0 tree w.r.t keys
    quickSort(tree -> c0Tree, tree -> max_c0_size); //TODO: check return value    


    // Get the parameters and metadata
    int num_level = tree-> max_level_in_ram;
    int num_block = tree-> num_blocks_per_level; 

    int empty_level = tree -> empty_ram_level;
    int empty_block = tree -> empty_ram_block;

    if (empty_level < num_level && empty_block < num_block) {

        int i_level, i_block;

        // Get space in the first block in level_available
        for (i_block = empty_block; i_block > 0; i_block--){

            // Set the flag to be true and move the pointer from the block on the left
            tree -> flag_ramTrees[empty_level * num_block + i_block] = true;
            tree -> ramTrees[empty_level* num_block + i_block] = tree -> ramTrees[empty_level* num_block + i_block-1]; 
        }

        tree -> ramTrees[empty_level* num_block] = NULL;

        for (i_level = empty_level - 1; i_level >= 0; i_level --){
            tree-> ramTrees[(i_level + 1)* num_block] = sortedMerge( &(tree-> ramTrees[i_level* num_block ]), tree -> max_c0_size * pow(num_block, i_level), &(tree-> ramTrees[i_level* num_block + 1]), tree -> max_c0_size * pow(num_block, i_level));
            tree-> flag_ramTrees[(i_level + 1)* num_block] = true;

            for (i_block = 0; i_block < num_block; i_block++){
                tree-> flag_ramTrees[i_level * num_block + i_block] = false;
                // ramTrees[i_level* num_block + i_block] = NULL;
            }
        }

        // Put the c0 tree in the first empty block
        tree -> ramTrees[0] = tree -> c0Tree;
        tree -> flag_ramTrees[0] = true;

        tree -> c0Tree = malloc(sizeof(lsmNode) * tree -> max_c0_size);
        tree -> c0_size = 0;

        tree -> empty_ram_block = num_block;
        tree -> empty_ram_level = num_level;    

        for (i_level = 0; i_level < num_level; i_level++){
            
            int this_level_available = 0;
            
            for (i_block = 0; i_block < num_block; i_block++){
                if (tree -> flag_ramTrees[i_level * num_block + i_block] == false){
                    this_level_available = 1;
                    tree -> empty_ram_block = i_block;
                    break;
                }
            }

            if (this_level_available){
                tree -> empty_ram_level = i_level;
                break;
            }
        }    
    }
    return 0;
}



/*********************************************************************/
/*****************************   RAM TREES ***************************/
/*********************************************************************/

/* In-place implementation of Quick Sort for node arrays*/
int quickSort(lsmNode * inputArray, int array_size){

    // The pivot node
    keyType piv;
    valueType piv_val;

    // Counters and ranges
    int i = 0, L, R;
    int beg[QS_MAX_LEVELS], end[QS_MAX_LEVELS];

    // Start wiht the full array
    beg[0] = 0;
    end[0] = array_size;


    while(i >= 0){

        L = beg[i];
        R = end[i] - 1;

        if (L < R){
            piv = inputArray[L].key;
            piv_val = inputArray[L].val;

            // TODO: If the maximum # of levels is reached: the algorithm fails!
            if (i == QS_MAX_LEVELS - 1){
                return -1;
            }

            // If the current array has more than two elements
            while(L < R){

                // Find the first entry from the right end that's smaller than the piv key
                while (inputArray[R].key >= piv && R > L) {
                    R--;
                }

                // If there is still more than two elements, i.e. there exists an entrt on the right that's smaller than the piv key
                // move the one smaller than piv to the left end --- the piv value has been recorded so don't worry
                if (L < R) {
                    inputArray[L++] = inputArray[R];
                }

                // Find the first entry from the left that's larger than the piv key
                while (inputArray[L].key <= piv && L < R) {
                    L++;
                }

                // If there is still more than two elements, i.e. there exists an entry on the left that's larger than the piv key
                // move the one larger than the entry from the left to the right end
                if (L < R) {
                    inputArray[R--] = inputArray[L];
                } 

            }

            inputArray[L].key = piv;
            inputArray[L].val = piv_val;

            beg[i + 1] = L + 1;
            end[i + 1] = end[i];
            end[i++] = L; 
        }

        else{
            i--;
        }
    }

    return 0;
}


/* Merge two sorted arrays */
lsmNode* sortedMerge(lsmNode ** source1Ref, int size1, lsmNode ** source2Ref, int size2)
{

    // Allocating memory for the result
    lsmNode * destArray = malloc(sizeof(lsmNode) * (size1 + size2));  //TODO: check malloc exceptions

    lsmNode * source1 = *source1Ref;
    lsmNode * source2 = *source2Ref;

    int ind1 = 0, ind2 = 0, ind_dest = 0;

    while (ind1 < size1 && ind2 < size2){
        if (source1[ind1].key <= source2[ind2].key){
            destArray[ind_dest++] = source1[ind1++];
        }
        else{
            destArray[ind_dest++] = source2[ind2++];       
        }
    }

    while (ind1 < size1){
        destArray[ind_dest++] = source1[ind1++];               
    }

    while (ind2 < size2){
        destArray[ind_dest++] = source2[ind2++];
    }

    free(*source1Ref);
    free(*source2Ref);
    *source1Ref = NULL;
    *source2Ref = NULL;

    return destArray;
}

/*********************************************************************/
/*****************************  Obsoleted  ***************************/
/*********************************************************************/
    /*
    // Traverse the meta data to see which block in which level is available


    // DEBUG
    // printf("Level available = %d \n", level_available);
    // printf("Block available = %d \n", block_available);
    */