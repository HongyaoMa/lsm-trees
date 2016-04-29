#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"


void ll_print_list(llnode_t * head) {

    llnode_t * current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

int ll_pop(llnode_t ** head) {

    int retval = -1;
    llnode_t * next_node = NULL;

    // If the list is empty
    if (*head == NULL) {
        return -1;
    }

    // Free the head and set the head to be the next node (or NULL)
    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}

int ll_remove_by_value(llnode_t ** head, int myval) {

    //If the value of the head is myval --- remove the head
    while ((*head != NULL) && (*head)->val == myval){
        ll_pop(head);
    }
    
    llnode_t *current = *head;
    llnode_t *temp_node = NULL;
    
    // While this is not the last node
    while (current != NULL && current->next != NULL){
        // If the next node has value myval
        if (current->next->val == myval){
            
            // Keep the next node's pointer
            temp_node = current->next;
            
            // Point the current node to the next of next node
            current->next = current->next->next;
            
            free(temp_node);
        }
		// proceed to the next node
        current = current-> next;
            
    }
	return 0;
}


int ll_free_list(llnode_t **head){

    // Original Implementation
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

    // Implementation using ll_pop
    while (*head != NULL){
        ll_pop(head);
    }
}