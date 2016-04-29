#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef struct llnode {
    int val;
    struct llnode * next;
} llnode_t;


void print_list(llnode_t * head);

int pop(llnode_t ** head);

int remove_by_value(llnode_t ** head, int myval);

#endif