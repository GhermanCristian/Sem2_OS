//A C program receives command line args numbers, and creates for each a thread that checks is the numbers are multiple of 2 or 5, incrementing a global variable. (use atoi)

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n = 0;
pthread_mutex_t mtx;

void* checkNumber(void* numberAsString){
	int number = atoi((char*)numberAsString);
	
	if (number % 2 == 0 || number % 5 == 0){
		pthread_mutex_lock(&mtx);
		n++;
		pthread_mutex_unlock(&mtx);
	}
	
	return NULL;
}

int main(int argc, char **argv){
	int i;
	pthread_t threads[argc];

	pthread_mutex_init(&mtx, NULL);
	for(i = 1; i < argc; i++){
		pthread_create(&threads[i], NULL, checkNumber, (void*)argv[i]);
	}
	
	for(i = 1; i < argc; i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mtx);
	printf("n = %d\n", n);

	return 0;
}
