// Testing the malloc exceptions 
// CS265 Project
// Hongyao Ma
// 05/05/2016

#include <stdio.h>
#include <stdlib.h>
#include "lsmtree.h"

int main() {

	long i, size = 10;

	int * int_ptr = malloc(sizeof(int) * size);
	if (int_ptr == NULL){
		fprintf(stderr, "failed to allocate memory.\n");
    	return -1;
	}

	for (i=0; i<size; i++)
		int_ptr[i] = i;

	free(int_ptr);

	if (1){
		fprintf(stderr, "Standard Error!\n");
    	return -1;
	}


	return 0;
	
}