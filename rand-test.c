#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linkedlist.h"

int main() {

	// Maximum random number:
	printf("The maximum number rand() generates is %d\n", RAND_MAX);
	// printf("The maximum number rand() generates is %d\n", RANDOM_MAX);

	// Generating a random array of size size

	int size = 10;
	int i;
	int *elements = malloc(sizeof(int)*size);

	// inizialize
	for (i = 0; i < size; ++i)
  		elements[i] = i;

  	// Set the random seed
	srand(time(NULL));

	// Swap!
	for (i = size - 1; i > 0; --i) {

  		// generate random index
  		// int w = rand() % i;
		long int w = random() % i;

  		// swap items
  		int temp = elements[i];
  		elements[i] = elements[w];
  		elements[w] = temp;
  	}

  	// Print the generated array
  	for (i=0; i<size; i++)
  		printf("%d ", elements[i]);

  	printf("\n");

  	// Free the allocated memory
  	free(elements);






	return 0;
}