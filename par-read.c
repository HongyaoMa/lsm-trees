// Testing parallel reading for the LSM Trees
// CS265 Project
// Hongyao Ma
// 05/11/2016

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#include "lsmtree.h"

typedef struct tag_lsm_get_arg{
	int thread_ind;
	int num_gets;
	keyType * inputKeyRef;
	valueType * outputValRef;
	lsmTree * tree;
} lsm_get_arg;

void *thread_get(void * arg_void_Ref);

int main() {

	char input_file[] = "data/data_100Mpairs.csv";
	char test_file[] = "data/data_10Mpairs.csv";

	int totalSize 	= 100000000;
	int testSize 	= 10000000;
	
	int num_threads = 8;

	// Parameters of the tree
	int max_c0_size = 100000;
	int max_level_in_ram = 15;
	int num_blocks_per_level = 2;
	int level1_multiplier = 1;


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

	FILE * fp_input = fopen(input_file,"r");	
	if (fp_input == NULL){
		fprintf(stderr, "Failed to open input data file!\n");
	}



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
	
	printf("Construction of the tree with %d elements took %f clock seconds!\n", totalSize, clock_spent);
	printf("Construction of the tree with %d elements took %f seconds!\n", totalSize, time_spent);

	// Print the meta data
	print_meta_data(testTree);
	
	// Print the full tree
	print_RAM_tree(testTree);

	/*************************** Testing gets and parallel gets ***************************/

	// Read in the testing dataset
	keyType * input_keys = malloc(sizeof(keyType) * testSize); 
	valueType * input_vals = malloc(sizeof(valueType) * testSize); 
	valueType * result_vals = malloc(sizeof(valueType) * testSize); 
	
	// Read in the testing data	
	FILE * fp_test = fopen(test_file,"r");
	for (i = 0; i < testSize; i++){
		fscanf(fp_test, "%d, %ld", input_keys+i, input_vals+i);
	}
	fclose(fp_test);	


	printf("\nFinished reading testing data!\n");

	/*
	// Get!
	begin = clock();
	for (i = 0; i < testSize; i++){	
		result_vals[i] = get_with_key(testTree, input_keys[i]);	
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\nGetting %d elements from the tree with %d elements took %f seconds!\n", testSize, totalSize, time_spent);	
	*/ 

	/************************************* Parallel Get ************************/

	clock_begin = clock();
	gettimeofday(&time_begin, NULL);

	// Thread heads
	pthread_t thread_id[num_threads];
	int thread_block_size = testSize / num_threads;

    // Structure for the inputs
    lsm_get_arg ** input_structs = malloc(sizeof(lsm_get_arg*) * num_threads);	

    // Initialization of the input arguments
    for (i = 0; i < num_threads; i++){

    	// Allocate memory to the input arguments
    	input_structs[i] = malloc(sizeof(lsm_get_arg));
    	(*(input_structs+i)) -> thread_ind = i;

    	// Number of elements to get from the tree
    	if (i <num_threads - 1){
    		(*(input_structs+i)) -> num_gets = thread_block_size;
    	}
    	else{
    		(*(input_structs+i)) -> num_gets = testSize - thread_block_size * (num_threads-1); 
    	}

    	// Pointers to the intput keys, output values and the tree
    	(*(input_structs+i)) -> inputKeyRef = input_keys + i * thread_block_size;
    	(*(input_structs+i)) -> outputValRef = result_vals + i * thread_block_size;
    	(*(input_structs+i)) -> tree = testTree;

		pthread_create(&thread_id[i], NULL , &thread_get, input_structs + i);
    }

    // Join the threads
    for(i = 0 ; i < num_threads; i++)
        pthread_join(thread_id[i], NULL);   

    // Printing the results of gets
    if (testSize < 50){
    	for (i = 0; i < testSize; i++){
    		printf("%d, %ld \n", input_keys[i], result_vals[i]);
    	}
    }

	clock_end = clock();
	gettimeofday(&time_end, NULL);

	// time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	// printf("\nParallelly getting %d elements from the tree with %d elements took %f seconds!\n", testSize, totalSize, time_spent);

	clock_spent = (double)(clock_end - clock_begin) / CLOCKS_PER_SEC;
	time_spent = (double) (time_end.tv_usec - time_begin.tv_usec) / 1000000 + (double) (time_end.tv_sec - time_begin.tv_sec);
	
	printf("Parallelly getting %d elements from the tree with %d elements took %f clock seconds!\n",  testSize, totalSize, clock_spent);
	printf("Parallelly getting %d elements from the tree with %d elements took %f seconds!\n",  testSize, totalSize, time_spent);


	// Free the memory
    for (i = 0; i < num_threads; i++){
    	free(input_structs[i]);
    }
    free(input_structs);
	lsmTree_free(&testTree);
	free(input_keys);
	free(input_vals);
	free(result_vals);

	return 0;
}

void * thread_get(void * arg_void_Ref){

	lsm_get_arg ** argRef = (lsm_get_arg **) arg_void_Ref;

	printf("Thread id is = %d \n", (*argRef) -> thread_ind);
	(*argRef) -> thread_ind = (*argRef) -> thread_ind*100;

	printf("Thread block size is = %d \n", (*argRef) -> num_gets);
	(*argRef) -> thread_ind = (*argRef) -> thread_ind*100;	

	int i;

	for (i = 0; i < (*argRef) -> num_gets; i++){	
		(*argRef) -> outputValRef[i] = get_with_key((*argRef) -> tree, (*argRef) -> inputKeyRef[i]);	
	}

	return NULL;
}