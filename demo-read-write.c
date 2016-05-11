// Demo of the reads and writes speed of the LSM Tree
// CS265 Project
// Hongyao Ma
// 05/03/2016

#include <stdio.h>
#include <stdlib.h>
#include "lsmtree.h"
#include <time.h>

int main() {

	char input_file[] = "data/data_100Mpairs.csv";
	char test_file[] = "data/test_10Mpairs.csv";

	int totalSize 	= 100000000;
	int testSize 	= 10000000;

	// Parameters of the tree
	int max_c0_size = 10000;
	int max_level_in_ram = 15;
	int num_blocks_per_level = 2;
	int level1_multiplier = 10;

	/*************************** Preparation ***************************/

	FILE * fp_input = fopen(input_file,"r");	
	if (fp_input == NULL){
		fprintf(stderr, "Failed to open the input data file!\n");
		return -1;
	}

	FILE * fp_test = fopen(test_file,"r");
	if (fp_test == NULL){
		fprintf(stderr, "Failed to open the testing data file!\n");
	}

	// The timer:
	clock_t clock_begin, clock_end;
	struct timeval  time_begin, time_end;

	double clock_spent, time_spent;

	/*************************** Constructing the tree from input data ***************************/

	// Initialization of the tree
	lsmTree * testTree;
	lsmTree_init(&testTree, max_c0_size, num_blocks_per_level, max_level_in_ram, level1_multiplier);
	// The print_tree_param function
	print_tree_param(testTree);

	// Read the data
	keyType inputKey;
	valueType inputValue;

	int i;

	// Filling up the tree
	clock_begin = clock();
	gettimeofday(&time_begin, NULL);

	for (i=0; i < totalSize; i++){
		fscanf(fp_input, "%d, %ld", &inputKey, &inputValue);		
		put_with_key(testTree, inputKey, inputValue);	
	}
	fclose(fp_input);

	// Recored the time
	clock_end = clock();
	gettimeofday(&time_end, NULL);

	clock_spent = (double)(clock_end - clock_begin) / CLOCKS_PER_SEC;
	time_spent = (double) (time_end.tv_usec - time_begin.tv_usec) / 1000000 + (double) (time_end.tv_sec - time_begin.tv_sec);
	
	printf("Construction of the tree with %d elements took %f cpu seconds!\n", totalSize, clock_spent);
	printf("Construction of the tree with %d elements took %f cpu seconds!\n", totalSize, time_spent);

	// Print the meta data
	print_meta_data(testTree);

	/*************************** Testing gets and puts ***************************/

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
	clock_begin = clock();
	gettimeofday(&time_begin, NULL);

	for (i=0; i < testSize; i++){	
		result_vals[i] = get_with_key(testTree, input_keys[i]);	
	}

	// Recored the time
	clock_end = clock();
	gettimeofday(&time_end, NULL);

	clock_spent = (double)(clock_end - clock_begin) / CLOCKS_PER_SEC;
	time_spent = (double) (time_end.tv_usec - time_begin.tv_usec) / 1000000 + (double) (time_end.tv_sec - time_begin.tv_sec);
	
	printf("\nGetting %d elements from the tree with %d elements took %f clock seconds!\n", testSize, totalSize, clock_spent);
	printf("\nGetting %d elements from the tree with %d elements took %f seconds!\n", testSize, totalSize, time_spent);

	// Puts
	clock_begin = clock();
	gettimeofday(&time_begin, NULL);

	for (i=0; i < testSize; i++){	
		put_with_key(testTree, input_keys[i], input_vals[i]);	
	}

	// Recored the time
	clock_end = clock();
	gettimeofday(&time_end, NULL);

	clock_spent = (double)(clock_end - clock_begin) / CLOCKS_PER_SEC;
	time_spent = (double) (time_end.tv_usec - time_begin.tv_usec) / 1000000 + (double) (time_end.tv_sec - time_begin.tv_sec);
	
	printf("\nPutting %d elements to the tree with %d elements took %f clock seconds!\n", testSize, totalSize, clock_spent);
	printf("\nPutting %d elements to the tree with %d elements took %f seconds!\n", testSize, totalSize, time_spent);

	// Free the memory
	lsmTree_free(&testTree);
	free(input_keys);
	free(input_vals);
	free(result_vals);

	return 0;
}
