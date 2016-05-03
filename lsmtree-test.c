// Testing the lsmTree
// CS265 Project
// Hongyao Ma
// 05/03/2016

#include <stdio.h>
#include <stdlib.h>
#include "lsmtree.h"

#define MAX_C0_SIZE 100

int main() {

	// print the MAX_C0_SIZE
	printf("The MAX_C0_SIZE is %d\n", MAX_C0_SIZE);

	// Initialization of the tree
	lsmTree * testTree = malloc(sizeof(lsmTree));
	testTree -> c0 = malloc(sizeof(lsmNode) * MAX_C0_SIZE);

    return 0;
}

