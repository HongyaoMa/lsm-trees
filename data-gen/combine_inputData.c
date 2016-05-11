// Converting 10 separate data files into one large file
// The CS265 Project
// Hongyao Ma
// 05/10/2016

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM_FILES 8

int main() {

	int i, i_file;

	int individual_size = 100000000;

	// Read the data
	int inputKey;
	long inputValue;
	FILE *fp_out;
	FILE ** inputFiles = malloc(sizeof(FILE*) * NUM_FILES);

	FILE *fp_in;

	// Parts of the filename
	char file_name_part_1[] = "output";
	char file_name_part_2[] = "0";
	char file_name_part_3[] = ".csv";

	printf("%s\n", file_name_part_1);
	printf("%s\n", file_name_part_2);
	printf("%s\n", file_name_part_3);		

	char *fileName_combined = malloc(strlen(file_name_part_1) + strlen(file_name_part_2) + strlen(file_name_part_3) +1);


	for (i_file = 0; i_file < NUM_FILES; i_file++){
		snprintf(file_name_part_2, 2, "%d", i_file);

		strcpy(fileName_combined, file_name_part_1);
		strcat(fileName_combined, file_name_part_2);
		strcat(fileName_combined, file_name_part_3);
		
		// *(inputFiles + i_file) = malloc(sizeof(FILE *));	
		// *(inputFiles + i_file) = fopen(fileName_combined,"r");
		inputFiles[i_file] = fopen(fileName_combined,"r");
		// fp_in = fopen(fileName_combined,"r");

		if (inputFiles[i_file] == NULL){
			fprintf(stderr, "Failed to open input data file %d!\n", i_file);
		}
		else{
			printf("Successfully opened file %s\n", fileName_combined);
		}

		printf("%p\n",inputFiles[i_file]);
		
	}

	fp_out = fopen("output_combined_800M.csv","w");
	if (fp_out == NULL){
		printf("Failed to create the output file!\n");
	}

	int inds[NUM_FILES];

	for (i_file = 0; i_file < NUM_FILES; i_file++){
		inds[i_file] = 0;
	}


	int total_num = 0;
	long iter_count = 0;
	int rand_ind;


	// The timer:
	clock_t begin, end;
	double time_spent;

	// Filling up the tree
	begin = clock();

	while (total_num <  individual_size * NUM_FILES){
		
		rand_ind = rand()%NUM_FILES;
		
		if (inds[rand_ind] < individual_size){

			fscanf(inputFiles[rand_ind], "%d, %ld", &inputKey, &inputValue);
			fprintf(fp_out, "%d, %ld\n", inputKey, inputValue);

			inds[rand_ind]++;
			total_num ++;
			iter_count ++;
		}
		else{
			iter_count ++;
			continue;
		}
	}
	printf("Total number of iterations is %ld\n", iter_count);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Combining the files took %f seconds!\n", time_spent);

	free(fileName_combined);

	/* TODO: Valgrind's error for closing
	for (i_file = 0; i_file< NUM_FILES; i_file++){
		close(*(inputFiles + i_file));
	}
	free(inputFiles);
	*/

	fclose(fp_out);

	return 0;
}