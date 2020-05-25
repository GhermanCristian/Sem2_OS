//Generati 100.000 de numere aleatoare si calculati suma lor utilizand 100 thread-uri. 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 100
#define NUMBER_COUNT 100000

typedef struct ThreadArgument{
	int *array;
	int startPos;
	int endPos;
}ThreadArgument;

int globalSum = 0;
pthread_mutex_t mtx;

void* numberSum(void* argument){
	ThreadArgument currentArgument = *(ThreadArgument*)argument;
	int localSum = 0;
	int i;

	for(i = currentArgument.startPos; i < currentArgument.endPos; i++){
		localSum += currentArgument.array[i];
	}

	pthread_mutex_lock(&mtx);
	globalSum += localSum;
	pthread_mutex_unlock(&mtx);

	return NULL;
} 

int main(){
	int numbers[NUMBER_COUNT];
	int i;
	int actualSum = 0;
	pthread_t threads[THREAD_COUNT];

	srand(time(NULL));
	pthread_mutex_init(&mtx, NULL);

	for(i = 0; i < NUMBER_COUNT; i++){
		numbers[i] = rand() % 20;
		actualSum += numbers[i];
	}

	for(i = 0; i < THREAD_COUNT; i++){
		ThreadArgument currentArgument;
		currentArgument.array = numbers;
		currentArgument.startPos = ( NUMBER_COUNT / THREAD_COUNT ) * i;
		currentArgument.endPos = ( NUMBER_COUNT / THREAD_COUNT ) * (i + 1);
		pthread_create(&threads[i], NULL, numberSum, (void*)&currentArgument);
	}

	for(i = 0; i < THREAD_COUNT; i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mtx);

	// these results are not equal, for some reason
	printf("Calculate sum = %d\n", globalSum);
	printf("Actual sum = %d\n", actualSum);

	return 0;
}
