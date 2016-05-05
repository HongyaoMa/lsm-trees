#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lsmsubtree.h"

// Maximum levels for the quick sort function
#define QS_MAX_LEVELS 1000


// The lsmSubTree
typedef struct tag_lsmSubTree{
    lsmNode * subTreeHead;
    int current_size;
    int maxSize;
    bool isSorted;
} lsmSubTree;


/* In-place implementation of Quick Sort for node arrays*/
// int quickSort(lsmNode *inputArray, int array_size);


/* Initializer */
int lsmSubTree_init(lsmSubTree ** subTreeRef, int input_maxSize, bool isSorted, bool allocMemory){
    
    // Allocation for the subtree itself
    (*subTreeRef) = malloc(sizeof(lsmSubTree));

    // Meta Data
    (*subTreeRef) -> current_size = 0;    
    (*subTreeRef) -> maxSize = input_maxSize;    
    (*subTreeRef) -> isSorted = isSorted;

    if (allocMemory) {
        (*subTreeRef) -> subTreeHead = malloc(sizeof(lsmNode) * input_maxSize); //TODO: catch memory exception
    }
    else{
        (*subTreeRef) -> subTreeHead = NULL;
    }
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


/************* Basic Subtree Operations **************/

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
        int first = 0, last = subTree-> current_size-1, mid = (first+last) / 2;
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
        printf("The Tree is Full!!\n"); //TODO: Change to error message!
        return -1;
    }

    // Put the key-value pair to the end of the tree
    (* subTreeRef) -> subTreeHead[(* subTreeRef) -> current_size].key = key_to_put;
    (* subTreeRef) -> subTreeHead[(* subTreeRef) -> current_size].val = val_to_put;
    (* subTreeRef) -> current_size ++;

    return 0;
}


/* Get the value with a key from the tree */
valueType subTree_get(lsmSubTree * subTree, keyType key_to_get){

    // TODO: do binary search for sorted trees

    int ind = subTree_lookup(subTree, key_to_get);

    if (ind >= 0)
        return subTree -> subTreeHead[ind].val;
    else
        return -1;    
}

/* Update the value for some key in the tree, return old value or -1 */
valueType subTree_update(lsmSubTree ** subTreeRef, keyType key_to_update, valueType val_to_update){

    int ind = subTree_lookup((* subTreeRef), key_to_update);

    if (ind >= 0){
        valueType tempVal = (* subTreeRef) -> subTreeHead[ind].val;
        (* subTreeRef) -> subTreeHead[ind].val = val_to_update;
        return tempVal;        
    }
    else{
        subTree_put(subTreeRef, key_to_update, val_to_update);
        return -1;
    }
}


/* Delete a key from the tree, return value or -1*/
valueType subTree_delete(lsmSubTree * subTree, keyType key_to_delete){
    
    int i;

    // Look for the key in the c0 tree
    for (i = subTree -> current_size-1; i >= 0; i--){
        if (subTree -> subTreeHead[i].key == key_to_delete){
            valueType tempVal = subTree -> subTreeHead[i].val;
            subTree -> subTreeHead[i].val = -1;
            return tempVal;
        }
    }    

    return -1;    
}

/********************   Meta Data Related  & IO ********************/

int get_subTree_size(lsmSubTree * subTree){
    return subTree -> current_size;
}


int set_subTree_sorted(lsmSubTree ** subTreeRef){

    (* subTreeRef)->isSorted = true;
}

int print_subTree_info(lsmSubTree * subTree){

    printf("\nPrinting Information for the Subtree!\n");

    printf("The current tree size is: %d\n", subTree -> current_size);
    printf("The maximum tree size is: %d\n", subTree -> maxSize);
    printf("If the tree is sorted? %d\n", subTree -> isSorted);

}

int print_full_subTree(lsmSubTree * subTree){

    if (subTree -> current_size > 50){
        printf("The tree is too big to be printed!\n");
        return -1;
    }

    int i;

    printf("\nPrinting the full subTree!\n");
    for (i=0; i < subTree -> current_size; i++){
        printf("%d, \t %ld\n",  subTree -> subTreeHead[i].key,  subTree -> subTreeHead[i].val);
    }
}

/************************* Sorting & Merging **************************/

/* Sorting a subTree using quick sort */
int subTree_sort(lsmSubTree ** subTreeRef){

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
        printf("The subtree is already sorted!\n"); //TODO: output error message!
        return -1;
    }

    return 0;
}


/* Merging a number of subtrees */
int subTree_merge(lsmSubTree** destRef, lsmSubTree ** subTreesRef, int num_subTrees){

    // Counters
    int i_subTree, totalSize = 0, ind_dest = 0;

    // Allocate memory to the temporary variables
    lsmNode ** tree_heads = malloc(sizeof(lsmNode*) * num_subTrees);
    int * subtree_sizes = malloc(sizeof(int) * num_subTrees);
    int * inds = malloc(sizeof(int) * num_subTrees);
    
    // Get the information from the tree and initialization of indices
    for (i_subTree = 0; i_subTree < num_subTrees; i_subTree++){

        // Heads of the subtrees
        tree_heads[i_subTree] = (*(subTreesRef + i_subTree)) -> subTreeHead;
        
        // Sizes of the subtrees and the total size
        subtree_sizes[i_subTree] = (*(subTreesRef + i_subTree)) -> current_size;
        totalSize += subtree_sizes[i_subTree];

        // Set the inds to be zero
        inds[i_subTree] = 0; 
    }

    // Initialization of the resulting tree, say it is sorted, and allocate memory
    lsmSubTree_init(destRef, totalSize, true, true);
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


/******************************* Obsoleted **************************/

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
