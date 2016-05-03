// Testing the lsmTree
// CS265 Project
// Hongyao Ma
// 05/03/2016

#include <stdio.h>
#include <stdlib.h>
#include "lsmtree.h"

int main() {

	// Initialization of the tree
	lsmTree * testTree = malloc(sizeof(lsmTree));
	lsm_init(testTree);

	// Free the tree
	lsm_free(testTree);

    return 0;
}

