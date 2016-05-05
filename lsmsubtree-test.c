// Testing the lsmNode and arrays of lsmNode
// CS 265 Final Project
// Hongyao Ma
// 05/03/2016

#include <stdio.h>
#include <stdlib.h>
#include "lsmsubtree.h"


int main() {

	int i;

	int maxSize = 6;
	bool allocMemory = true;
	bool isSorted = false;

	/* Basic functions 
	// Initialization of the subtree
	lsmSubTree * subTree;
	lsmSubTree_init(&subTree, maxSize, isSorted, allocMemory);
	
	// Put data into the subtree
	for (i = 0; i < maxSize-1; i++){
		subTree_put(&subTree, rand() % 10, random()%100);
		//subTree_put(&subTree, i, random()%100);
	}

	// Set the tree to be sorted
	// set_subTree_sorted(&subTree);

	// Printing the tree information
	print_full_subTree(subTree);

	// Sort the subtree
	subTree_sort(&subTree);


	// Trying to add another element to a full tree
	// subTree_put(&subTree, 1, 1);

	// Printing the tree information
	print_subTree_info(subTree);

	// Print the full tree
	print_full_subTree(subTree);


	// Get the value with key 2
	printf("\nThe value corresponding to key 2 is %ld \n", subTree_get(subTree, 2));

	// Get the value with key 7, which is non-existent
	printf("\nThe value corresponding to key 7 is %ld \n", subTree_get(subTree, 7));

	// Update the value with key 2 to 100
	printf("\nUpdate the value with key 2 to 100");
	subTree_update(&subTree, 2, 100);
	print_full_subTree(subTree);

	// Update the value with key 3 to 33, which doesn't exist --- a new key is added
	printf("\nUpdate the value with key 3 to 33, which doesn't exist");
	subTree_update(&subTree, 3, 33);
	print_full_subTree(subTree);	

	// Delete the key 1
	printf("\nDelete the key 1");
	subTree_delete(subTree, 1);
	print_full_subTree(subTree);

	// Free the subtree
	lsmSubTree_free(&subTree);
*/

	/* Testing the merge sorted function */

	lsmSubTree * subTree1;
	lsmSubTree * subTree2;

	lsmSubTree_init(&subTree1, maxSize, isSorted, allocMemory);
	lsmSubTree_init(&subTree2, maxSize, isSorted, allocMemory);

	// Put data into the subtree
	for (i = 0; i < maxSize-1; i++){
		subTree_put(&subTree1, rand() % 10, random()%100);
		subTree_put(&subTree2, rand() % 10, random()%100);
	}

	// Set the tree to be sorted
	// set_subTree_sorted(&subTree);

	// Printing the tree information
	printf("Printing subtree 1:\n");
	print_full_subTree(subTree1);

	printf("Printing subtree 2:\n");	
	print_full_subTree(subTree2);

	// Sort the subtree
	subTree_sort(&subTree1);
	subTree_sort(&subTree2);

	// Printing the tree information
	printf("Printing subtree 1:\n");
	print_full_subTree(subTree1);

	printf("Printing subtree 2:\n");	
	print_full_subTree(subTree2);


	lsmSubTree * mergedTree;
	lsmSubTree ** subTrees = malloc(sizeof(lsmSubTree *) * 2);

	* subTrees = subTree1;
	* (subTrees+1) = subTree2;

	/* Merging a number of subtrees */
	subTree_merge(&mergedTree, subTrees, 2);

	printf("Print the merged tree!\n");
	print_full_subTree(mergedTree);

	lsmSubTree_free(&mergedTree);
	
	// lsmSubTree_free(&subTree1);
	// lsmSubTree_free(&subTree1);

	free(subTrees);

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

/*
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

	printf("\nThe original array is: \n");
	for (i = 0; i<10; i++){
		printf("The key of the lsmNode is %d\n", node_array[i].key);
		printf("The value of the is %ld\n", node_array[i].val);		
	}

	// mergeSort_rec(&node_array, 10);
	quickSort(node_array, 10);

	printf("\nThe soretd array is: \n");
	for (i = 0; i<10; i++){
		printf("The key of the lsmNode is %d\n", node_array[i].key);
		printf("The value of the is %ld\n", node_array[i].val);		
	}

	free(node_array);
*/

    return 0;
}