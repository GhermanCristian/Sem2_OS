#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 3

int contor = 0;
int threadID[] = {0, 1, 2};
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cnt = PTHREAD_COND_INITIALIZER;

void* increaseContor(void* argument){
	int i;
	printf("Start increase contor\n");
	for(i = 0; i < 7; i++){
		printf("thread = %d     contor = %d\n", *(int*)argument, contor);
		sleep(rand() % 3);
		pthread_mutex_lock(&mtx);
		contor++;

		if (contor == 12){
			printf("Signal\n");
			pthread_cond_signal(&cnt);
		}
	
		pthread_mutex_unlock(&mtx);
	}
	printf("End increase contor\n");

	return NULL;
}

void* checkContor(void* argument){
	printf("Start check contor\n");
	pthread_mutex_lock(&mtx);
	while(contor <= 12){
		pthread_cond_wait(&cnt, &mtx); //it will automatically release the mutex while it waits
		printf("Received signal\n");
		break;
	}
	pthread_mutex_unlock(&mtx);
	printf("End check contor\n");
	return NULL;
}

int main(){
	int i;
	pthread_t threads[THREAD_COUNT];

	pthread_create(&threads[0], NULL, checkContor, &threadID[0]);
	pthread_create(&threads[1], NULL, increaseContor, &threadID[1]);
	pthread_create(&threads[2], NULL, increaseContor, &threadID[2]);

	for(i = 0; i < THREAD_COUNT; i++){
		pthread_join(threads[i], NULL);
	}

	return 0;
}
