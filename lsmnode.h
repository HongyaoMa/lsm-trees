#ifndef _LSMNODE_H
#define _LSMNODE_H

typedef int keyType;
typedef long valueType;

typedef struct tag_lsmNode{
    keyType key;
    valueType val;
} lsmNode;

/* Merge two sorted arrays */
lsmNode* sortedMerge(lsmNode ** source1Ref, int size1, lsmNode ** source2Ref, int size2);


/* Recursive implementation of MergeSort for node arrays*/
int mergeSort_rec(lsmNode ** arrayRef, int array_size);


/* In-place implementation of MergeSort for node arrays*/
int mergeSort(lsmNode ** arrayRef, int array_size);





#endif