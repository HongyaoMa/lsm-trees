// Testing the lsmNode and arrays of lsmNode
// CS 265 Final Project
// Hongyao Ma
// 05/03/2016

#include <stdio.h>
#include <stdlib.h>
#include "lsmnode.h"


int main() {

	int i;

	/*

	// Testing the lsmNode
	lsmNode * test_node = malloc(sizeof(lsmNode));
	test_node -> key  = 5;
	test_node -> val  = 15;

	printf("The key of the lsmNode is %d\n", test_node->key );
	printf("The value of the is %ld\n", test_node->val);

	free(test_node);

	// Generate and display an array of lsmNodes
	lsmNode * node_array = malloc(sizeof(lsmNode)*10);

	for (i = 0; i<10; i++){
		node_array[i].key = rand() % 100;
		node_array[i].val = random();
	}

	for (i = 0; i<10; i++){
		printf("The key of the lsmNode is %d\n", node_array[i].key);
		printf("The value of the is %ld\n", node_array[i].val);		
	}

	free(node_array);

	*/

	// Testing the sortedMerge function

	lsmNode * array1 = malloc(sizeof(lsmNode)*5);
	lsmNode * array2 = malloc(sizeof(lsmNode)*5);

	for (i=0; i<5; i++){
		array1[i].key = 2*i + 1;
		array1[i].val = random();	
		array2[i].key = 2*i + 2;
		array2[i].val = random();	
	}

	for (i = 0; i<5; i++){
		printf("The key of the array1 is %d\n", array1[i].key);
		printf("The value of the is %ld\n", array1[i].val);		
	}

	for (i = 0; i<5; i++){
		printf("The key of the array2 is %d\n", array2[i].key);
		printf("The value of the is %ld\n", array2[i].val);		
	}

	lsmNode * destArray = sortedMerge(&array1, 5, &array2, 5);

	printf("\nPrinting the merged arrays!!!\n");

	for (i = 0; i<10; i++){
		printf("The key of the destArray is %d\n", destArray[i].key);
		printf("The value of the is %ld\n", destArray[i].val);		
	}

	free(destArray);


	// Testing the mergeSort_rec function

	lsmNode * node_array = malloc(sizeof(lsmNode)*10);

	for (i = 0; i<10; i++){
		node_array[i].key = rand() % 100;
		node_array[i].val = random();
	}

	printf("\n The original array is: \n");
	for (i = 0; i<10; i++){
		printf("The key of the lsmNode is %d\n", node_array[i].key);
		printf("The value of the is %ld\n", node_array[i].val);		
	}

	// mergeSort_rec(&node_array, 10);
	mergeSort(&node_array, 10);

	printf("\n The soretd array is: \n");
	for (i = 0; i<10; i++){
		printf("The key of the lsmNode is %d\n", node_array[i].key);
		printf("The value of the is %ld\n", node_array[i].val);		
	}

	free(node_array);

    return 0;
}