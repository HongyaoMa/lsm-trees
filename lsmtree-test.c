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

	// The print_tree_param function
	print_tree_param(testTree);

	/************************* Basic Tree Manipulations ************************/

	// Filling up the c0 tree, get size, and print the c0 tree
	int i;
	for (i=0; i < 30; i++){
		put_with_key(testTree, rand()%100, random());
	}

	/* 
	// Testing get_c0_size
	printf("Size of the C0 Tree is %d\n", get_c0_size(testTree));

	// Testing print_c0_tree
	print_c0_tree(testTree);

	// Testing get_with_key
	printf("The value corresponding to key 846930886 is %ld\n", get_with_key(testTree, 846930886));
	printf("The value corresponding to key 5 is %ld\n", get_with_key(testTree, 5));

	// Testing update with key
	valueType old_value = update_with_key(testTree, 846930886, 100);
	printf("The old value of key 846930886 is %ld\n", old_value);

	old_value = update_with_key(testTree, 5, 500);
	printf("The old value of key  is %ld\n", old_value);	

	// print_c0_tree(testTree);
	*/

	print_meta_data(testTree);
	print_RAM_tree(testTree);

	// Free the tree
	lsm_free(&testTree);

    return 0;
}

