#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define NUM_THREADS 3
#define ARRAY_SIZE 10

struct thread_fill_data{
	int thread_num;
	//TODO: add fields to this struct to pass in thread's start location, array size, and fill value
	float* start_location;
	int array_size;
	float fill_value;
};

void fillArray(float* arr, int size, float val){
	//TODO: draw stack diagram here
	for(int i=0; i < size; i++){
		arr[i] = val;
	}
}

void *threadMain(void * data) {
	struct thread_fill_data* thread_input = (struct thread_fill_data*)data;
	int thread_num = thread_input->thread_num;
	//TODO: unpack the fields you added to the struct into local variables
    printf("Thread %d has started\n", thread_num);
	float* start_location = thread_input->start_location;
	int array_size = thread_input -> array_size;
	float fill_value = thread_input -> fill_value;
	//TODO: call fillArray appropriately
	fillArray(start_location, array_size, fill_value);

    printf("Thread %d has finished\n", thread_num);

	return NULL;
}

int main(void) {
 	pthread_t threadIDs[NUM_THREADS];
	struct thread_fill_data* thread_inputs[NUM_THREADS];

	//The threads are filling this array
	float* data_array = malloc(ARRAY_SIZE * sizeof(float));

	//Initialize the thread inputs
	for(int i=0; i < NUM_THREADS; i++){
		thread_inputs[i] = malloc(NUM_THREADS * sizeof(struct thread_fill_data));
  		thread_inputs[i]->thread_num = i;
			thread_inputs[i]->start_location = data_array + (NUM_THREADS*i);
			if(i = NUM_THREADS - 1){
				thread_inputs[i]->array_size = ceil(ARRAY_SIZE/NUM_THREADS);
			}
			else{
				thread_inputs[i]->array_size = floor(ARRAY_SIZE/NUM_THREADS);

			}

			thread_inputs[i]->fill_value = i;

		//TODO: initialize the rest of the data in the thread_fill_data structs -
	}

	//Launch all threads
	printf("launching threads\n");
	for(int i = 0; i < NUM_THREADS; i++) {
		if(pthread_create(&threadIDs[i], NULL, threadMain, (void *) thread_inputs[i])) {
			perror("Error creating threads\n");
			return EXIT_FAILURE;
		}
	}

	//Block the main thread until all other threads return
	printf("waiting for threads\n");
	for(int i = 0; i < NUM_THREADS; i++) {
		if(pthread_join(threadIDs[i], NULL) != 0) {
			fprintf(stderr, "Error joning threads\n");
			return EXIT_FAILURE;
		}else{
			printf("joined thread %d\n", (int)thread_inputs[i]->thread_num);
			free(thread_inputs[i]);
		}
	}

	//Print the results (but only if the array is small-ish)
	if(ARRAY_SIZE <= 100){
		printf("filled array:\n[ ");
		for(int i=0; i<ARRAY_SIZE; i++){
			printf("%.2f ", data_array[i]);
		}
		printf("]\n");
	}

	free(data_array);
	printf("all done!\n");
	return EXIT_SUCCESS;
}
