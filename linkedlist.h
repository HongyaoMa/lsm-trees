#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef struct llnode {
    int val;
    struct llnode * next;
} llnode_t;


void ll_print_list(llnode_t * head);

int ll_pop(llnode_t ** head);

int ll_remove_by_value(llnode_t ** head, int myval);

int ll_free_list(llnode_t **head);

#endif