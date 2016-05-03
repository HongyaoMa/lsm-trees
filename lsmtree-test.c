// Testing the lsmTree
// CS265 Project
// Hongyao Ma
// 05/03/2016

#include <stdio.h>
#include <stdlib.h>
#include "lsmtree.h"

int main() {

	// maximum c0 size
	int max_c0_size = 1000000;

	

	// Initialization of the tree
	lsmTree * testTree;
	lsm_init(&testTree, max_c0_size);

	printf("Size of the C0 Tree is %d\n", get_c0_size(testTree));

	// Free the tree
	lsm_free(&testTree);


    return 0;
}

