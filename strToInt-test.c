// Testing the integer to string function and reading files
// The CS265 Project
// Hongyao Ma
// 05/10/2016


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lsmtree.h"

#define NUM_FILES 10


int main() {

	// Print a normal string
	char fileName[] = "data/data_32pairs.csv";
	printf("Greeting message: %s\n", fileName);

	// Open the file using a string and print the file name
	FILE *fp;

	fp = fopen(fileName,"r");
	if (fp == NULL){
		fprintf(stderr, "Failed to open input data file!\n");
	}
	else{
		printf("Successfully opened the file %s!\n", fileName);
	}

	fclose(fp);

	// Convert a single digit integer to a string
	int i = 5;
	char str[2];
	snprintf(str, 2, "%d", i);
	printf("The integer is %s!\n", str);

	char file_name_part_1[] = "output_small_";
	char file_name_part_2[2];
	snprintf(file_name_part_2, 2, "%d", i);
	char file_name_part_3[] = ".csv";

	printf("Are we here?\n");

	char *fileName_combined = malloc(strlen(file_name_part_1) + strlen(file_name_part_2) + strlen(file_name_part_3) +1);

	strcpy(fileName_combined, file_name_part_1);
	strcat(fileName_combined, file_name_part_2);
	strcat(fileName_combined, file_name_part_3);

	printf("Greeting message: %s\n", fileName_combined);

	return 0;
}