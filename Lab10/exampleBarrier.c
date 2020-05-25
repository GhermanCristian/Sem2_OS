#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 10
pthread_barrier_t barrier;

void* threadFunction(void* argument){
	int seconds = 1 + rand() % 3;
	int threadID = *(int*)argument;
	printf("Thread %d waits for %d seconds\n", threadID, seconds);
	sleep(seconds);
	printf("Thread %d woke up\n", threadID);
	pthread_barrier_wait(&barrier);
	printf("Thread %d is done\n", threadID);
	return NULL;	
}

int main(){
	int i;
	int threadID[THREAD_COUNT];
	pthread_t threads[THREAD_COUNT];

	pthread_barrier_init(&barrier, NULL, THREAD_COUNT);

	for(i = 0; i < THREAD_COUNT; i++){
		threadID[i] = i;
		pthread_create(&threads[i], NULL, threadFunction, (void*)&threadID[i]);
	}
	for(i = 0; i < THREAD_COUNT; i++){
		pthread_join(threads[i], NULL);
	}

	pthread_barrier_destroy(&barrier);
	
	return 0;
}
