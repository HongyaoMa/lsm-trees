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
	lsmTree_init(&testTree, max_c0_size, num_blocks_per_level, max_level_in_ram);

	// The print_tree_param function
	print_tree_param(testTree);


	/************************* Basic Tree Manipulations ************************/

	// Filling up the c0 tree, get size, and print the c0 tree
	int i;
	for (i=0; i < 32; i++){
		put_with_key(testTree, rand()%100, random());
	}

	/*
	// Print the meta data
	print_meta_data(testTree);

	// Testing get_with_key
	printf("\nTesting get_with_key\n");
	printf("The value corresponding to key 86 is %ld\n", get_with_key(testTree, 86));
	printf("The value corresponding to key 5 is %ld\n", get_with_key(testTree, 5));

	// Print the full tree
	print_RAM_tree(testTree);

	// Testing update with key
	printf("\nTesting update_with_key\n");
	valueType old_value = update_with_key(testTree, 86, 100);
	printf("The old value of key 86 is %ld\n", old_value);

	old_value = update_with_key(testTree, 5, 500);
	printf("The old value of key 5 is %ld\n", old_value);	

	// Print the full tree
	print_RAM_tree(testTree);

	// Testing the update function
	printf("\nTesting the update function!\n");
	put_with_key(testTree, rand()%100, random());

	*/

	// Print the meta data
	print_meta_data(testTree);

	// Print the full tree
	print_RAM_tree(testTree);

	// Free the tree
	lsmTree_free(&testTree);

    return 0;
}

