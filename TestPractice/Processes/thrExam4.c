#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_COUNT 10
#define NUMBER_COUNT 55 // better safe than sorry
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int globalSum = 1;
int globalArray[NUMBER_COUNT];
int globalArrLen = 0;

void* threadFunction(void* argument){
	while(1){
		pthread_mutex_lock(&mtx);
		if (globalSum >= 55){
			pthread_mutex_unlock(&mtx);
			break;
		}
		else{
			pthread_mutex_unlock(&mtx);
		}
		
		pthread_mutex_lock(&mtx);
		globalSum++;
		if (globalSum % 2 == 0 || globalSum / 10 % 10 == 2){
			globalArray[globalArrLen++] = globalSum;
		}
		else{
			printf("%d\n", globalSum);
		}
		pthread_mutex_unlock(&mtx);
	}

	return NULL;
}

int main(){
	int i;
	pthread_t threads[THREAD_COUNT];

	for(i = 0; i < THREAD_COUNT; i++){
		pthread_create(&threads[i], NULL, threadFunction, NULL);
	}
	for(i = 0; i < THREAD_COUNT; i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mtx);
	for(i = 0; i < globalArrLen; i++){
		printf("arr[%d] = %d\n", i, globalArray[i]);
	}

	return 0;
}
