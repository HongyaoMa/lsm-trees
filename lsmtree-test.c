// Testing the lsmTree
// CS265 Project
// Hongyao Ma
// 05/03/2016

#include <stdio.h>
#include <stdlib.h>
#include "lsmtree.h"

int main() {

	// maximum c0 size
	int max_c0_size = 5;
	int max_level_in_ram = 2;
	int num_blocks_per_level = 2;
	
	// Initialization of the tree
	lsmTree * testTree;
	lsm_init(&testTree, max_c0_size, num_blocks_per_level, max_level_in_ram);

	// Filling up the c0 tree, get size, and print the c0 tree
	int i;
	for (i=0; i < max_c0_size; i++){
		put_with_key(testTree, rand(), random());
	}

	// Testing get_c0_size
	printf("Size of the C0 Tree is %d\n", get_c0_size(testTree));

	// Testing print_c0_tree
	print_c0_tree(testTree);


	/*************** Testing of meta data related functions **************/


	// Free the tree
	lsm_free(&testTree);


    return 0;
}

