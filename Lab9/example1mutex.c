#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_COUNT 100
#define ELEMENT_COUNT 1000

typedef struct ThreadArgument{
	int *array;
	int startIndex;
	int endIndex;
}ThreadArgument;

int globalSum = 0;
int n = 0;
pthread_mutex_t mtx;

void* arraySum(void *argument){
	int i;
	int localSum = 0;
	ThreadArgument currentArgument = *(ThreadArgument*)argument;

	for(i = currentArgument.startIndex; i < currentArgument.endIndex; i++){
		localSum += currentArgument.array[i];
	}

	pthread_mutex_lock(&mtx);
	n++;
	globalSum += localSum;
	pthread_mutex_unlock(&mtx);

	return 0;
}

int main(){
	int i;
	int array[ELEMENT_COUNT];
	pthread_t threads[THREAD_COUNT];
	
	pthread_mutex_init(&mtx, NULL);

	for (i = 0; i < ELEMENT_COUNT; i++){
		array[i] = 1;
	}

	for (i = 0; i < THREAD_COUNT; i++){
		ThreadArgument currentArgument;
		currentArgument.array = array;
		currentArgument.startIndex = ( ELEMENT_COUNT / THREAD_COUNT ) * i;
		currentArgument.endIndex = ( ELEMENT_COUNT / THREAD_COUNT ) * ( i + 1 );
		pthread_create(&threads[i], NULL, arraySum, (void*)&currentArgument);
	}

	// this may be called before all threads have finished their execution
	printf("Between for loops\n");

	for (i = 0; i < THREAD_COUNT; i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mtx);

	printf("Global sum = %d\n", globalSum);
	printf("n = %d\n", n);
	return 0;
}
