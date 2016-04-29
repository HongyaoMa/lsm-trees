#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node * next;
} node_t;

void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

int pop(node_t ** head) {
    int retval = -1;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}

int remove_by_value(node_t ** head, int myval) {
    /* TODO: fill in your code here */

    //If the value of the head is myval --- remove the head
    while ((*head)->val == myval){
        pop(head);
    }
    
    node_t *current = *head;
    node_t *temp_node = NULL;
    
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

int main() {
    node_t * test_list = malloc(sizeof(node_t));
    test_list->val = 3;
    test_list->next = malloc(sizeof(node_t));
    test_list->next->val = 2;
    test_list->next->next = malloc(sizeof(node_t));
    test_list->next->next->val = 3;
    test_list->next->next->next = malloc(sizeof(node_t));
    test_list->next->next->next->val = 4;
    test_list->next->next->next->next = NULL;

    remove_by_value(&test_list, 3);

    print_list(test_list);
}
