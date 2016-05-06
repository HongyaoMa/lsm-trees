// Demo of the basic functions of the LSM tree
// CS265 Project
// Hongyao Ma
// 05/05/2016

#include <stdio.h>
#include <stdlib.h>
#include "lsmtree.h"

int main() {

	/****************************** Read the data ******************************/

	// Read the data from file
	int totalSize = 32;
	FILE *fp;
	//fp = fopen("/home/hma/Desktop/lsm-trees/data_32keys_largeKeys.csv","r");
	fp = fopen("data/data_32pairs_largevals.csv","r");

	keyType * input_keys = malloc(sizeof(keyType) * totalSize); 
	valueType * input_vals = malloc(sizeof(valueType) * totalSize); 

	int i;
	for (i = 0; i < totalSize; i++){
		fscanf(fp, "%d, %ld", input_keys+i, input_vals+i);
	}
	fclose(fp);


	/*************************** Constructing the tree***************************/
	// maximum c0 size
	int max_c0_size = 5;
	int max_level_in_ram = 3;
	int num_blocks_per_level = 2;
	
	// Initialization of the tree
	lsmTree * testTree;
	lsmTree_init(&testTree, max_c0_size, num_blocks_per_level, max_level_in_ram);

	// The print_tree_param function
	print_tree_param(testTree);

	// Filling up the c0 tree, get size, and print the c0 tree
	for (i=0; i < totalSize; i++){
		put_with_key(testTree, input_keys[i], input_vals[i]);
	}

	// Print the meta data
	print_meta_data(testTree);

	// Print the full tree
	print_RAM_tree(testTree);


	/****************************** DEMO ******************************/
	keyType currentKey;
	valueType currentVal, returnVal;

	// Demo get
	printf("Please type in a key to get: ");
	scanf("%d", &currentKey);
	printf("The value corresponding to key %d is %ld\n", currentKey, get_with_key(testTree, currentKey));

	printf("Please type in another key to get: ");
	scanf("%d", &currentKey);
	printf("The value corresponding to key %d is %ld\n", currentKey, get_with_key(testTree, currentKey));
	

	// Demo put
	printf("Please type in a key to put: ");
	scanf("%d", &currentKey);
	printf("Please type in a value to put: ");
	scanf("%ld", &currentVal);
	put_with_key(testTree, currentKey, currentVal);
	print_RAM_tree(testTree);
	
	// Demo update
	printf("Please type in a key to update: ");
	scanf("%d", &currentKey);
	printf("Please type in a value to update: ");
	scanf("%ld", &currentVal);
	returnVal = update_with_key(testTree, currentKey, currentVal);
	print_RAM_tree(testTree);	
	printf("The old value of key %d is %ld\n", currentKey, returnVal);

	printf("Please type in another key to update: ");
	scanf("%d", &currentKey);
	printf("Please type in another value to update: ");
	scanf("%ld", &currentVal);
	returnVal = update_with_key(testTree, currentKey, currentVal);
	print_RAM_tree(testTree);	
	printf("The old value of key %d is %ld\n", currentKey, returnVal);	

	// Demo delete
	printf("Please type in a key to delete: ");
	scanf("%d", &currentKey);
	returnVal = delete_with_key(testTree, currentKey);
	print_RAM_tree(testTree);
	printf("The value of key %d is %ld\n", currentKey, returnVal);	


	printf("Please type in another key to delete: ");
	scanf("%d", &currentKey);
	returnVal = delete_with_key(testTree, currentKey);
	print_RAM_tree(testTree);
	printf("The value of key %d is %ld\n", currentKey, returnVal);	

	// Free the memories
	lsmTree_free(&testTree);
	free(input_keys);
	free(input_vals);

	return 0;
}