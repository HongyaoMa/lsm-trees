#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct tag_arg_struct{
	int arg1;
	int arg2;
} arg_struct;

void *thread_function(void * arg_void_Ref)
{
	arg_struct ** argRef = (arg_struct **) arg_void_Ref;

	printf("arg1 * 100 = %d \n", (*argRef) -> arg1);
	(*argRef) -> arg2 = (*argRef) -> arg1*100;

	/* the function must return something - NULL will do */
	return NULL;
}

int main()
{
    int noOfThread= 4;
    pthread_t thread_id[noOfThread];
    int x[noOfThread];
    int i;
    int status;

    // Structure for the inputs
    arg_struct ** input_structs = malloc(sizeof(arg_struct*) * noOfThread);

    // Create the threads to do the work
    for(i =0; i < noOfThread; i++)
    {
    	input_structs[i] = malloc(sizeof(arg_struct));

    	(*(input_structs+i)) -> arg1 = i;
    	//(*(input_structs+i)) -> arg2 = i*2;

        pthread_create(&thread_id[i], NULL , &thread_function, input_structs + i);
    } 

    // Join the threads
    for(i=0; i < noOfThread; i++)
        pthread_join(thread_id[i], NULL);   

    // Output the results
    for (i=0; i < noOfThread; i++){
    	printf("arg2[i] = %d \n", (*(input_structs + i)) -> arg2);
    }

    return 0;
}