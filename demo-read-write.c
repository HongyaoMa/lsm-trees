// Demo of the reads and writes speed of the LSM Tree
// CS265 Project
// Hongyao Ma
// 05/03/2016

#include <stdio.h>
#include <stdlib.h>
#include "lsmtree.h"
#include <time.h>

int main() {

	// Testing data
	// FILE * fp = fopen("data/data_100Mpairs.csv","r");
	// FILE * fp_test = fopen("data/test_10Mpairs.csv","r");

	FILE * fp = fopen("data/data_1Bpairs.csv","r");
	FILE * fp_test = fopen("data/test_100Mpairs.csv","r");

	int totalSize 	= 1000000000;
	int testSize 	= 100000000;
	
	// Parameters of the tree
	int max_c0_size = 100000;
	int max_level_in_ram = 13;
	int num_blocks_per_level = 2;
	int level1_multiplier = 1;

	/*************************** Constructing the tree from input data ***************************/

	// Initialization of the tree
	lsmTree * testTree;
	lsmTree_init(&testTree, max_c0_size, num_blocks_per_level, max_level_in_ram, level1_multiplier);
	// The print_tree_param function
	print_tree_param(testTree);


	// Read the data
	keyType inputKey;
	valueType inputValue;



	if (fp == NULL){
		fprintf(stderr, "Failed to open input data file!\n");
	}

	// The timer:
	clock_t begin, end;
	double time_spent;

	int i;

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

	


	keyType * input_keys = malloc(sizeof(keyType) * testSize); 
	valueType * input_vals = malloc(sizeof(valueType) * testSize); 
	valueType * result_vals = malloc(sizeof(valueType) * testSize); 

	// Read in the testing data
	for (i = 0; i < testSize; i++){
		fscanf(fp_test, "%d, %ld", input_keys+i, input_vals+i);
	}
	fclose(fp_test);	

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