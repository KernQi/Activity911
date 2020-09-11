#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define NUM_THREADS 4

void *threadIncrement(void * data) {
	int* i_ptr = (int*)data;

	for(int i=0; i < 1000000; i++){
		(*i_ptr)++;
	}

	return NULL;
}

int main(void) {
 	pthread_t threadIDs[NUM_THREADS];
	int i=0;

	for(int j=0; j < NUM_THREADS; j++){
		if(pthread_create(&threadIDs[j], NULL, threadIncrement, (void *) &i)) {
			perror("Error creating threads\n");
			return EXIT_FAILURE;
		}
	}

	for(int j = 0; j < NUM_THREADS; j++) {
		if(pthread_join(threadIDs[j], NULL) != 0) {
			fprintf(stderr, "Error joning threads\n");
			return EXIT_FAILURE;
		}
	}

	printf("i = %d\n", i);
	return EXIT_SUCCESS;
}
