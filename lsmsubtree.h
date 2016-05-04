#ifndef _LSMSUBTREE_H
#define _LSMSUBTREE_H

typedef int keyType;
typedef long valueType;

typedef int bool;
#define true 1
#define false 0

// The Node
typedef struct tag_lsmNode{
    keyType key;
    valueType val;
} lsmNode;


// The lsmSubTree
typedef struct tag_lsmSubTree lsmSubTree;


/* Initializer */
int lsmSubTree_init(lsmSubTree ** subTreeRef, int input_maxSize, int isSorted, bool allocMemory);


/* Destructor */
int lsmSubTree_free(lsmSubTree ** subTreeRef);









/* Merge two sorted arrays */
lsmNode* sortedMerge(lsmNode ** source1Ref, int size1, lsmNode ** source2Ref, int size2);

/* In-place implementation of Quick Sort for node arrays*/
int quickSort(lsmNode *inputArray, int array_size);


/************************** Obsoleted **********************************/


#endif