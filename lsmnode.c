#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lsmnode.h"

// Maximum levels for the quick sort function
#define QS_MAX_LEVELS 1000

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


/* Recursive implementation of MergeSort for node arrays*/
// Reference: https://gist.github.com/mycodeschool/9678029

int mergeSort_rec(lsmNode ** arrayRef, int array_size){


    // If the size of the array is smaller than 2: no need to do anyting
    if (array_size < 2)
        return;

    // The mid-point
    int mid = array_size / 2; 

    lsmNode * leftArray = malloc(sizeof(lsmNode) * mid);
    lsmNode * rightArray = malloc(sizeof(lsmNode) * (array_size- mid));

    int i;
    lsmNode * inputArray = *arrayRef;

    for (i = 0; i < mid; i++) {
        leftArray[i] = inputArray[i];
    }

    for (i = mid; i < array_size; i++) {
        rightArray[i-mid] = inputArray[i];
    }

    mergeSort_rec(&leftArray, mid);
    mergeSort_rec(&rightArray, array_size - mid);

    // Free the original array since space will be re-allocated
    free(*arrayRef);

    *arrayRef = sortedMerge(&leftArray, mid, &rightArray, array_size - mid);
}

/* In-place implementation of Quick Sort for node arrays*/
// http://alienryderflex.com/quicksort/
// https://en.wikipedia.org/wiki/Quicksort#C

int quickSort(lsmNode ** arrayRef, int array_size){

    printf("Here?\n");
    int i = 0, L, R;
    int beg[QS_MAX_LEVELS], end[QS_MAX_LEVELS];

    beg[0] = 0;
    end[0] = array_size;

    keyType piv;
    valueType piv_val;

    lsmNode * inputArray = *arrayRef;

    while(i >= 0){
        
        L = beg[i];
        R = end[i] - 1;

        if (L < R){
            piv = inputArray[L].key;
            piv_val = inputArray[L].val;

            // TODO: what is this doing?
            if (i == QS_MAX_LEVELS - 1){
                return -1;
            }

            while(L < R){
                while (inputArray[R].key >= piv && L < R) {
                    R--;
                }

                if (L < R) {
                    inputArray[L++] = inputArray[R];
                }

                while (inputArray[L].key <= piv && L < R) {
                    L++;
                }
                if (L < R) {
                    inputArray[R--] = inputArray[L];
                } 
            }

            inputArray[L].key = piv;
            inputArray[L].val = piv_val;

            beg[i + 1] = L+1;
            end[i + 1] = end[i];
            end[i++] = L;
        }
        else{
            i--;
        }
    }

    return 0;
}






/************************** Obsoleted **********************************/

/* In-place implementation of MergeSort for node arrays*/
// http://stackoverflow.com/questions/2571049/how-to-sort-in-place-using-the-merge-sort-algorithm
// https://github.com/liuxinyu95/AlgoXY/blob/algoxy/sorting/merge-sort/src/mergesort.c

int mergeSort(lsmNode ** arrayRef, int array_size){

    return 0;
}