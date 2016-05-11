// Converting 10 separate data files into one large file
// The CS265 Project
// Hongyao Ma
// 05/10/2016


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_FILES 1

int main() {

	int i, i_file;

	int individual_size = 100000000;

	// Read the data
	int inputKey;
	long inputValue;
	FILE *fp;

	for (i_file = 0; i_file < NUM_FILES; i_file++){
		fp = fopen("data_100Mpairs.csv","r");
		if (fp == NULL){
			fprintf(stderr, "Failed to open input data file %d!\n", i_file);
		}
	}

	/* 
	// The timer:
	clock_t begin, end;
	double time_spent;

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

	*/

	return 0;
}