#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef struct llnode {
    int val;
    struct llnode * next;
} llnode_t;


// Print the list
void ll_print_list(llnode_t * head);

// Traverse the list to compute its length
int ll_length(llnode_t *head);

// Push a node to the head of the list
int ll_push(llnode_t **headRef, int data);

// Pop the head of the list and return its value
int ll_pop(llnode_t ** headRef);

// Append a node at the end of the list
int ll_append(llnode_t **headRef, int data);

// Remove all nodes with value myval from the list
int ll_remove_by_value(llnode_t ** headRef, int myval);

// Free the memory allocate for the whle list
int ll_free_list(llnode_t **headRef);


/***************** Merge Sort Related Functions ******************/

/* Move the head node from source to dest */
void ll_moveNode(llnode_t ** destRef, llnode_t ** sourceRef);


/* Merge two sorted lists that are already sorted in increasing order */
llnode_t * ll_sortedMerge(llnode_t ** list1Ref, llnode_t ** list2Ref);

/* Split a linked list in two */
int ll_split(llnode_t *source, llnode_t ** frontRef, llnode_t ** backRef);


/* The Merge Sort function */
int ll_mergeSort(llnode_t ** headRef);




#endif