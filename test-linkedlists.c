#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

int main() {

    // Constructing a list
    llnode_t * test_list = malloc(sizeof(llnode_t));

    test_list->val = 3;
    test_list->next = malloc(sizeof(llnode_t));
    test_list->next->val = 2;
    test_list->next->next = malloc(sizeof(llnode_t));
    test_list->next->next->val = 3;
    test_list->next->next->next = malloc(sizeof(llnode_t));
    test_list->next->next->next->val = 4;
    test_list->next->next->next->next = NULL;

    // print the list before removing all "3"'s
    printf("List before removing 3\n");
    ll_print_list(test_list);

    // print the list after removing all 3's
    printf("List after removing 3\n");
    ll_remove_by_value(&test_list, 3);

    // DEBUG
    // ll_remove_by_value(&test_list, 2);
    // ll_remove_by_value(&test_list, 4);  

    ll_print_list(test_list);

    // Freeing the spae?
    // DEBUG
    //printf("Free the list!\n");

    ll_free_list(&test_list);
}
