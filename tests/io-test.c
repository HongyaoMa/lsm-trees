// Testing the input and output functions in C
// CS 265 Project
// Hongyao Ma
// 05/02/2016

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {

	int char_input;
	int int_input;

	/*************** Standard IO   *****************

	// getchar and putchar
	char_input = getchar();
	putchar(char_input);
	printf("\n");


	// scanf
	scanf("%d", &int_input);
	printf("%d\n", int_input);

	// TODO: getline

	// TODO: get at the end of a file

	*/

	/**************** File manipulation ***************

	// open the read and write files
	FILE * read_pointer;
	FILE * write_pointer;

	read_pointer = fopen("file_in.txt", "r");
	write_pointer = fopen("file_out.txt", "w");

	// getc & putc
	char_input = getc(read_pointer);
	putc(char_input, write_pointer);

	// char_input = getc(read_pointer);
	// putc(char_input, write_pointer);	

	// fscanf & fprintf
	fscanf(read_pointer, "%d", &int_input);
	fprintf(write_pointer, "\n%d", int_input);

	// TODO: fgets & fputs

	// close the files
	fclose(read_pointer);
	fclose(write_pointer);	

	*/

	/*************** Lower-level IO *****************





	return 0;
}
