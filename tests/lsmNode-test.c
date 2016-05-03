// Testing the lsmNode and arrays of lsmNode
// CS 265 Final Project
// Hongyao Ma
// 05/03/2016

#include <stdio.h>
#include <stdlib.h>
#include "lsmtree.h"

int main() {

	// Testing the lsmNode
 	printf("Here?\n");
	lsmNode * test_node = malloc(sizeof(lsmNode));
	test_node -> key  = 5;
	test_node -> val  = 15;

	printf("The key of the lsmNode is %d\n", test_node->key );
	printf("The value of the is %ld\n", test_node->val);

	free(test_node);

	// Array of lsmNodes
	lsmNode * test_c0Tree = malloc(sizeof(lsmNode)*10);
	int i;

	for (i = 0; i<10; i++){
		test_c0Tree[i].key = i;
		test_c0Tree[i].val = i*10;
	}

	for (i = 0; i<10; i++){
		printf("The key of the lsmNode is %d\n", test_c0Tree[i].key);
		printf("The value of the is %ld\n", test_c0Tree[i].val);		
	}

	free(test_c0Tree);

    return 0;
}