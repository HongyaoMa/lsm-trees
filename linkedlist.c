#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"


void print_list(llnode_t * head) {
    llnode_t * current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

int pop(llnode_t ** head) {
    int retval = -1;
    llnode_t * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}

int remove_by_value(llnode_t ** head, int myval) {

    //If the value of the head is myval --- remove the head
    while ((*head)->val == myval){
        pop(head);
    }
    
    llnode_t *current = *head;
    llnode_t *temp_node = NULL;
    
    // While this is not the last node
    while (current->next != NULL){
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
