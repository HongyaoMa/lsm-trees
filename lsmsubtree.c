#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "lsmsubtree.h"


// Maximum levels for the quick sort function
#define QS_MAX_LEVELS 1000

// The entry node
typedef struct tag_lsmNode{
    keyType key;
    valueType val;
} lsmNode;


// The lsmSubTree
typedef struct tag_lsmSubTree{
    lsmNode * subTreeHead;
    int current_size;
    int maxSize;
    bool isSorted;
} lsmSubTree;


/************************* Utility Functions **************************/

/* In-place implementation of Quick Sort for node arrays*/
int quickSort(lsmNode *inputArray, int array_size);

/***************** Initializer and Destructor Functions *****************/

/* Initializer */
int lsmSubTree_init(lsmSubTree ** subTreeRef, int input_maxSize, bool isSorted, bool allocMemory){
    
    // Allocation for the subtree itself
    (*subTreeRef) = malloc(sizeof(lsmSubTree));
    if ((*subTreeRef) == NULL){
        fprintf(stderr, "Subtree initialization failed!\n");
        return -1;
    }

    // Meta Data
    (*subTreeRef) -> current_size = 0;    
    (*subTreeRef) -> maxSize = input_maxSize;    
    (*subTreeRef) -> isSorted = isSorted;

    if (allocMemory) {
        (*subTreeRef) -> subTreeHead = malloc(sizeof(lsmNode) * input_maxSize); //TODO: catch memory exception
        if ((*subTreeRef) -> subTreeHead == NULL){
            fprintf(stderr, "Subtree memory allocation failed!\n");
            return -1;
        }
    }
    else{
        (*subTreeRef) -> subTreeHead = NULL;
    }
    return 0;
}


/* Destructor */
int lsmSubTree_free(lsmSubTree ** subTreeRef){

    // Free the memory for the array saved in the subtree
    if ( (*subTreeRef) -> subTreeHead != NULL){
        free((*subTreeRef) -> subTreeHead);
    }

    // Free the subtree itself
    free(* subTreeRef);
    return 0;
}


/********************** Basic Subtree Operations ********************/

/* Find the location of a certain key. Return -1 if non-existant */
int subTree_lookup(lsmSubTree *subTree, keyType key_to_lookup){

    int i;

    // If the Tree is not sorted --- searching from the newest element
    if (!subTree -> isSorted){
        for (i = subTree -> current_size - 1; i >= 0; i--){
            if (subTree -> subTreeHead[i].key == key_to_lookup){
                return i;
            }
        }
    }
    // Binary search on a sorted array
    else{
        int first = 0, last = subTree-> current_size - 1, mid = (first+last) / 2;
        while(first <= last){
            if (subTree-> subTreeHead[mid].key < key_to_lookup){
                first = mid + 1;
            }
            else if (subTree-> subTreeHead[mid].key == key_to_lookup){
                return mid;
            }
            else {
                last = mid - 1;
            }
            mid = (first+last) / 2;
        }
    }
    // If not found:
    return -1;
}


/* Put a key and value pair into the tree */
int subTree_put(lsmSubTree ** subTreeRef, keyType key_to_put, valueType val_to_put){

    // If the maximum size is reached
    if ((* subTreeRef) -> current_size == (* subTreeRef) -> maxSize){
        fprintf(stderr, "Attempt to add nodes to a full subtree!\n");
        return -1;
    }

    // Put the key-value pair to the end of the tree
    (* subTreeRef) -> subTreeHead[(* subTreeRef) -> current_size].key = key_to_put;
    (* subTreeRef) -> subTreeHead[(* subTreeRef) -> current_size].val = val_to_put;
    (* subTreeRef) -> current_size ++;

    return 0;
}


/* Get the value with a key from the tree */
valueType subTree_get(lsmSubTree * subTree, keyType key_to_get)
{
    int ind = subTree_lookup(subTree, key_to_get);
    
    // If the key is found, return the value
    if (ind >= 0)
        return subTree -> subTreeHead[ind].val;

    // Otherwise: return the TOMBSTONE
    else
        return TOMBSTONE;    
}

/* Update the value for some key in the tree, return old value or TOMBSTONE */
valueType subTree_update(lsmSubTree ** subTreeRef, keyType key_to_update, valueType val_to_update)
{
    int ind = subTree_lookup((* subTreeRef), key_to_update);

    // If the key is found: return the original value
    if (ind >= 0){
        valueType tempVal = (* subTreeRef) -> subTreeHead[ind].val;
        (* subTreeRef) -> subTreeHead[ind].val = val_to_update;
        return tempVal;        
    }
    // Otherwise: return the TOMBSTONE
    return TOMBSTONE;
}


/* Delete a key from the tree, return value or TOMBSTONE*/
valueType subTree_delete(lsmSubTree * subTree, keyType key_to_delete)
{    
    // Look up the key in the tree
    int ind = subTree_lookup(subTree, key_to_delete);
    
    // If the key is found
    if (ind >= 0){
        valueType tempVal = subTree -> subTreeHead[ind].val;
        subTree -> subTreeHead[ind].val = TOMBSTONE;
        return tempVal;        
    }
    else{
        return TOMBSTONE; 
    }
}

/********************   Meta Data Related  & IO ********************/

int get_subTree_size(lsmSubTree * subTree){
    return subTree -> current_size;
}

int set_subTree_sorted(lsmSubTree ** subTreeRef){
    (* subTreeRef) -> isSorted = true;
    return 0;
}

int print_subTree_info(lsmSubTree * subTree)
{
    printf("\nPrinting Information for the Subtree!\n");

    printf("The current tree size is: %d\n", subTree -> current_size);
    printf("The maximum tree size is: %d\n", subTree -> maxSize);
    printf("If the tree is sorted? %d\n", subTree -> isSorted);

    return 0;

}

int print_full_subTree(lsmSubTree * subTree)
{
    if (subTree -> current_size > 50){
        fprintf(stderr, "The tree is too big to be printed!\n");
        return -1;
    }

    int i;

    // printf("\nPrinting the full subTree!\n");
    for (i=0; i < subTree -> current_size; i++){
        printf("%d, \t %ld\n",  subTree -> subTreeHead[i].key,  subTree -> subTreeHead[i].val);
    }

    return 0;
}

/************************* Sorting & Merging **************************/

/* Sorting a subTree using quick sort */
int subTree_sort(lsmSubTree ** subTreeRef)
{
    // If the subtree is not yet sorted
    if (! (* subTreeRef) -> isSorted){

        // If quick sort exited normally
        if (!quickSort((* subTreeRef) -> subTreeHead, (* subTreeRef) -> current_size)){
            (* subTreeRef) -> isSorted = true;
            return 0;
        }
        // If quick sort failed
        else{
            printf("Quick sort failed! \n"); //TODO: error message
            return -1;
        }
    }
    // If the subtree is already sorted: note: we don't do a check here
    else{
        printf("Warning: the subtree is already sorted!\n"); 
    }

    return 0;
}


/* Merging a number of subtrees */
int subTree_merge(lsmSubTree** destRef, lsmSubTree ** subTreesRef, int num_subTrees)
{
    // One tree --- trivial case:
    if (num_subTrees == 1){
        *destRef = * subTreesRef;
        *subTreesRef = NULL;
        return 0;
    }

    // If there are more than one trees to merge

    // Counters
    int i, totalSize = 0, ind_dest = 0;

    // Allocate memory to the temporary variables
    lsmNode ** tree_heads = malloc(sizeof(lsmNode*) * num_subTrees);
    int * subtree_sizes = malloc(sizeof(int) * num_subTrees);
    int * inds = malloc(sizeof(int) * num_subTrees);

    if (tree_heads == NULL || subtree_sizes == NULL || inds == NULL){
        fprintf(stderr, "Auxilary variables for subTreeMerge failed to initialize!\n");
        return -1;
    }


    // Get the information from the tree and initialization of indices
    for (i = 0; i < num_subTrees; i++){

        // Heads of the subtrees
        tree_heads[i] = (*(subTreesRef + i)) -> subTreeHead;
        
        // Sizes of the subtrees and the total size
        subtree_sizes[i] = (*(subTreesRef + i)) -> current_size;
        totalSize += subtree_sizes[i];

        // Set the inds to be zero
        inds[i] = 0; 
    }

    // Initialization of the resulting tree, say it is sorted, and allocate memory
    if (lsmSubTree_init(destRef, totalSize, true, true) != 0){
        fprintf(stderr, "Initialization of the resulting merged tree failed\n");
        return -1;
    }
    

    lsmNode *  result_TreeHead = (*destRef) -> subTreeHead;
    (*destRef) -> current_size = totalSize;

    // Simple case when there are only two blocks to merge
    if (num_subTrees == 2){        
        while (inds[0] < subtree_sizes[0] && inds[1] < subtree_sizes[1]){
            if (tree_heads[0][inds[0]].key <= tree_heads[1][inds[1]].key){
                result_TreeHead[ind_dest++] = (*tree_heads)[inds[0] ++];
            }
            else{
                result_TreeHead[ind_dest++] = tree_heads[1][inds[1] ++];       
            }
        }
        while (inds[0] < subtree_sizes[0]){
            result_TreeHead[ind_dest++] = tree_heads[0][inds[0]++];               
        }
        while (inds[1] < subtree_sizes[1]){
            result_TreeHead[ind_dest++] = tree_heads[1][ inds[1]++];
        }
    }
    // Merging multiple trees!
    else{

        keyType min_key;
        int min_tree;

        bool trees_exhausted = false;

        /* 
        keyType * currentKeys =  malloc(sizeof(keyType) * num_subTrees);
        // Put the head of thea tree in the temp counter;
        for (i = 0; i < num_subTrees; i++){
            currentKeys[i] = tree_heads[i][0].key;
        }
        */
        
        while(!trees_exhausted){

            // Initialization of the find minimum algorithm
            min_key = INT_MAX;
            min_tree = 0;

            // Find the minimum of the trees TODO: Optimize the statements
            for (i = 0; i < num_subTrees; i++){
                if (inds[i] < subtree_sizes[i]){
                    if (tree_heads[i][inds[i]].key <= min_key){
                        min_key = tree_heads[i][inds[i]].key;
                        min_tree = i;
                    }
                }
            }

            // Move the minimum to the destination
            result_TreeHead[ind_dest++] = tree_heads[min_tree][inds[min_tree]++];

            // Check if we have exhausted the tree
            trees_exhausted = true;
            for (i=0; i < num_subTrees; i++){
                if (inds[i] < subtree_sizes[i]){
                    trees_exhausted = false;
                    break;
                }
            }
        }
        
        // free(currentKeys);
    }

    // Free the blocks that are in this level and set the pointers to NULL
    for (i = 0; i < num_subTrees; i++){
        lsmSubTree_free(subTreesRef + i);
        *(subTreesRef + i) = NULL;
    }

    // Free the temporary variables
    free(inds);
    free(tree_heads);
    free(subtree_sizes);

    return 0;
}

/******************************* Utility Functions **************************/

/* In-place implementation of Quick Sort for node arrays*/
// http://alienryderflex.com/quicksort/
// https://en.wikipedia.org/wiki/Quicksort#C

int quickSort(lsmNode * inputArray, int array_size)
{
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
