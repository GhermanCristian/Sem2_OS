//Scrieti un program care determina valoarea maxima dintr-un sir de 100 000 de elemente. Sirul va fi parcurs folosind 10 thread-uri.  

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 10
#define NUMBER_COUNT 100000

typedef struct ThreadArgument{
	int *array;
	int startPos;
	int endPos;
}ThreadArgument;

int globalMax = 0;
pthread_mutex_t mtx;

void* numberSum(void* argument){
	ThreadArgument currentArgument = *(ThreadArgument*)argument;
	int localMax = 0;
	int i;

	for(i = currentArgument.startPos; i < currentArgument.endPos; i++){
		if (localMax < currentArgument.array[i]){
			localMax = currentArgument.array[i];
		}
	}

	pthread_mutex_lock(&mtx);
	if (globalMax < localMax){
		globalMax = localMax;
	}
	pthread_mutex_unlock(&mtx);

	return NULL;
} 

int main(){
	int numbers[NUMBER_COUNT];
	int i;
	int actualMax = 0;
	pthread_t threads[THREAD_COUNT];
	ThreadArgument threadArg[THREAD_COUNT];

	srand(time(NULL));
	pthread_mutex_init(&mtx, NULL);

	for(i = 0; i < NUMBER_COUNT; i++){
		numbers[i] = rand() % 999999999;
		if (actualMax < numbers[i]){
			actualMax = numbers[i];
		}
	}

	for(i = 0; i < THREAD_COUNT; i++){
		threadArg[i].array = numbers;
		threadArg[i].startPos = ( NUMBER_COUNT / THREAD_COUNT ) * i;
		threadArg[i].endPos = ( NUMBER_COUNT / THREAD_COUNT ) * (i + 1);
		pthread_create(&threads[i], NULL, numberSum, (void*)&threadArg[i]);
	}

	for(i = 0; i < THREAD_COUNT; i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mtx);

	printf("Calculated max = %d\n", globalMax);
	printf("Actual max = %d\n", actualMax);

	return 0;
}
