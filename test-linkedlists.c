#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

int main() {

    // Construct a test list
    llnode_t * test_list = NULL;
    ll_push(&test_list, 3);
    ll_append(&test_list, 2);     
    ll_append(&test_list, 3);  
    ll_append(&test_list, 4);  

    // Testing the push function
    ll_push(&test_list, 6);

    // Testing the append function
    ll_append(&test_list, 5);

    // Testing the length function 
    printf("The length of the list is %d\n", ll_length(test_list));

    // print the list before removing all "3"'s
    printf("List before removing 3\n");
    ll_print_list(test_list);

    // print the list after removing all 3's
    printf("List after removing 3\n");
    ll_remove_by_value(&test_list, 3);
    ll_print_list(test_list);




    /*********** Tests related to Merge Sort **************/

    // Testing the function move node
    llnode_t * new_list = NULL;
    ll_moveNode(&new_list, &test_list);
    ll_print_list(test_list);
    ll_print_list(new_list);

    // Merging two lists

    llnode_t * list1 = NULL;
    ll_append(&list1, 1);
    ll_append(&list1, 3);
    ll_append(&list1, 5);
    ll_print_list(list1);    

    llnode_t * list2 = NULL;
    ll_append(&list2, 2);
    ll_append(&list2, 4);
    ll_append(&list2, 6);
    ll_print_list(list2);  

    llnode_t * sortedList = NULL;
    sortedList = ll_sortedMerge(list1, list2);
    ll_print_list(sortedList);      

    /************* Tests for an empty list **************/
    /*
    printf("Tests for an empty list:\n");

    llnode_t *empty_list = NULL;

    // Length of an empty list
    printf("The length of an empty list is %d\n", ll_length(empty_list));

    // Push to an empty list 
    ll_push(&empty_list, 3);
    ll_print_list(empty_list);
    ll_pop(&empty_list);

    // Popping from an empty list
    printf("Return value from popping an empty list is %d \n", ll_pop(&empty_list));

    // Append to an empty list
    ll_append(& empty_list, 5);    
    ll_print_list(empty_list);
    ll_pop(&empty_list);

    // Printing an empty list
    ll_print_list(empty_list);

    // free the testing list
    ll_free_list(&empty_list);    
    */



    // Free the memory!
    ll_free_list(&test_list);
    ll_free_list(&new_list);
    //ll_free_list(&list1);
    //ll_free_list(&list2);
    //ll_free_list(&sortedList);

}



/*****************  OBSOLETED & DEBUG ******************/

    /*
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
    */