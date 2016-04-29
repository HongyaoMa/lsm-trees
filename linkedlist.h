#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef struct node {
    int val;
    struct node * next;
} node_t;


void print_list(node_t * head);

int pop(node_t ** head);

int remove_by_value(node_t ** head, int myval);

#endif