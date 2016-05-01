#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linkedlist.h"

/* Printing the list */
void ll_print_list(llnode_t * head) {

    llnode_t * current = head;
    if (current == NULL){
        printf("The list to be printed is empty!\n");
        return;
    }

    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

/* Traverse the list to compute its length */
int ll_length(llnode_t * head){
    llnode_t * current = head;
    int length = 0;

    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}


// Push a node to the head of the list
int ll_push(llnode_t **headRef, int data){

    llnode_t* newNode = malloc(sizeof(llnode_t));

    newNode->val = data;
    newNode->next = *headRef;
    *headRef = newNode;

    return 0;
}

// Pop the head of the list and return its value
int ll_pop(llnode_t ** headRef) {

    int retval = -1;
    llnode_t * next_node = NULL;

    // If the list is empty
    if (*headRef == NULL) {
        return -1;
    }

    // Free the head and set the head to be the next node (or NULL)
    next_node = (*headRef)->next;
    retval = (*headRef)->val;
    free(*headRef);
    *headRef = next_node;

    return retval;
}

// Append a node at the end of the list
int ll_append(llnode_t **headRef, int data){

    // generate a new node
    llnode_t* newNode = malloc(sizeof(llnode_t));
    newNode ->val = data;
    newNode -> next = NULL;

    llnode_t* current = *headRef;

    // If the list is empty: set the head to the new node
    if (current == NULL){
        *headRef = newNode;
    }
    else{
        // Find the end of the list and append the node
        while (current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
    }

    return 0;
}


// Remove all nodes with value myval from the list
int ll_remove_by_value(llnode_t ** headRef, int myval) {

    //If the value of the head is myval --- remove the head
    while ((*headRef != NULL) && (*headRef)->val == myval){
        ll_pop(headRef);
    }
    
    llnode_t *current = *headRef;
    llnode_t *temp_node = NULL;
    
    // While this is not the last node
    while (current != NULL && current->next != NULL){

        // If the next node has value myval
        if (current->next->val == myval){
            temp_node = current->next;  // Keep the next node's pointer
            current->next = current->next->next;    // Point the current node to the next of next node
            free(temp_node);
        }
		// proceed to the next node
        current = current-> next;
            
    }
	return 0;
}

// Free the memory allocate for the whle list
int ll_free_list(llnode_t **headRef){

    // Implementation using ll_pop
    while (*headRef != NULL){
        ll_pop(headRef);
    }
}


/************************** Merge Sort **************************/



/* Move the head node from source to dest */
// The source list must not be empty
void ll_moveNode(llnode_t ** destRef, llnode_t ** sourceRef)
{
    /* the front source node  */
    llnode_t* newNode = *sourceRef;
    assert(newNode != NULL);
 
    /* Advance the source pointer */
    *sourceRef = newNode->next;
 
    /* Link the old dest off the new node */
    newNode->next = *destRef;
 
    /* Move dest to point to the new node */
    *destRef = newNode;
}


/* Merge two sorted lists that are already sorted in increasing order */
llnode_t * ll_sortedMerge(llnode_t ** list1Ref, llnode_t ** list2Ref){
    llnode_t * resultHead = NULL;
    llnode_t ** lastPtrRef = &resultHead;

    llnode_t * list1 = *list1Ref;
    llnode_t * list2 = *list2Ref;

    while (1){
        if (list1 == NULL){
            *lastPtrRef = list2;
            break;
        }   
        else if (list2 == NULL){
            *lastPtrRef = list1;
            break;
        }
        if (list1->val <= list2->val) {
            *lastPtrRef = list1;
            list1 = list1 -> next;
            // ll_moveNode(lastPtrRef, &list1);
        }
        else{
            *lastPtrRef = list2;
            list2 = list2 -> next;
            // ll_moveNode(lastPtrRef, &list2);
        }

        lastPtrRef = &((*lastPtrRef)->next); 
    }

    *list1Ref = NULL;
    *list2Ref = NULL;

    return(resultHead);
}

/* Split a linked list in two */
int ll_split(llnode_t *source, llnode_t ** frontRef, llnode_t ** backRef){
    

    // Set the front to point to the resource
    *frontRef = source;

    // If the source list is empty
    if ((source == NULL) || (source->next == NULL)){
        *backRef = NULL;      
        return 0;
    }

    else{        

        // Fast and slow node
        llnode_t * fast = source->next;
        llnode_t * slow = source;   

        // int slowCount = 1;
        // int fastCount = 2;

        while (fast != NULL){

            fast = fast -> next;
            // fastCount ++;

            // printf("Slow = %d, fast = %d?\n", slowCount, fastCount);

            if (fast != NULL){
                fast = fast -> next;
                slow = slow -> next;
                // fastCount++;
                // slowCount++;
            }
        }

        // Set the back to be the slow node
        *backRef = slow->next;
        slow->next = NULL;        
    }

    return 0;
}


/* The Merge Sort function */
int ll_mergeSort(llnode_t ** headRef){

    return 0;
}


/*************************  OBSOLETED***************************/

    // Original Implementation of ll_free_list
    /*
    // If the list is empty
    if (*head == NULL) return 0;
    
    // Temporary node
    llnode_t * next_node = NULL;

    // If the head's next node is not empty, i.e. there are more than two nodes
    while ((*head)->next != NULL){
        next_node = (*head) -> next;
        free(*head);
        (*head) = next_node;
    }

    // free the last node
    free(*head);
    */