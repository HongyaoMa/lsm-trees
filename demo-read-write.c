// Demo of the reads and writes speed of the LSM Tree
// CS265 Project
// Hongyao Ma
// 05/03/2016

#include <stdio.h>
#include <stdlib.h>
#include "lsmtree.h"
#include <time.h>

int main() {

	// The timer:
	clock_t begin, end;
	double time_spent;

	int i;

	/*************************** Constructing the tree from input data ***************************/

	// Construction of the tree
	int max_c0_size = 100000;
	int max_level_in_ram = 13;
	int num_blocks_per_level = 4;
	
	// Initialization of the tree
	lsmTree * testTree;
	lsmTree_init(&testTree, max_c0_size, num_blocks_per_level, max_level_in_ram);
	// The print_tree_param function
	print_tree_param(testTree);


	// Read the data
	keyType inputKey;
	valueType inputValue;
	FILE *fp;

	int totalSize = 100000000;
	fp = fopen("data/data_100Mpairs.csv","r");
	if (fp == NULL){
		fprintf(stderr, "Failed to open input data file!\n");
	}

	// Filling up the tree
	begin = clock();	
	for (i=0; i < totalSize; i++){
		fscanf(fp, "%d, %ld", &inputKey, &inputValue);		
		put_with_key(testTree, inputKey, inputValue);	
	}
	fclose(fp);

	// Recored the time
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Construction of the tree with %d elements took %f seconds!\n", totalSize, time_spent);

	// Print the meta data
	print_meta_data(testTree);


	/*************************** Testing gets and puts ***************************/

	// Read in the testing dataset

	int testSize = 10000000;
	fp = fopen("data/test_10Mpairs.csv","r");

	keyType * input_keys = malloc(sizeof(keyType) * testSize); 
	valueType * input_vals = malloc(sizeof(valueType) * testSize); 
	valueType * result_vals = malloc(sizeof(valueType) * testSize); 

	// Read in the testing data
	for (i = 0; i < testSize; i++){
		fscanf(fp, "%d, %ld", input_keys+i, input_vals+i);
	}
	fclose(fp);	

	printf("\n!!!!FINISHED READING TEST DATA!!!!\n");

	// Gets
	begin = clock();	
	for (i=0; i < testSize; i++){	
		result_vals[i] = get_with_key(testTree, input_keys[i]);	
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\nGetting %d elements from the tree with %d elements took %f seconds!\n", testSize, totalSize, time_spent);


	// Puts
	begin = clock();	
	for (i=0; i < testSize; i++){	
		put_with_key(testTree, input_keys[i], input_vals[i]);	
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\nPutting %d elements to the tree with %d elements took %f seconds!\n", testSize, totalSize, time_spent);



	// Free the memory
	lsmTree_free(&testTree);
	free(input_keys);
	free(input_vals);
	free(result_vals);

	return 0;
}