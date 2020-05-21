//Write a program that creates 5 threads, giving each thread a string as parameter. Each thread will count and add to the global variables v and n as follows: the number of vowels contained by the string added to v, and the number of digits contained in the string added to n.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define THREAD_COUNT 5
#define MAX_STRING_LENGTH 40

int n = 0;
int v = 0;
pthread_mutex_t mtx;

void* processString(void* string){
	char* str = (char*)string;
	int len = strlen(str) - 1;
	int i;
	int noVowels = 0; // local
	int noDigits = 0; // local

	for(i = 0; i < len; i++){
		if (strchr("aeiouAEIOU", str[i]) != NULL){
			noVowels++;
		}
		else if(strchr("0123456789", str[i]) != NULL){
			noDigits++;
		}
		//printf("str[ %d ] = %c\n", i, str[i]);
	}

	pthread_mutex_lock(&mtx);
	n += noVowels;
	v += noDigits;
	pthread_mutex_unlock(&mtx);
	
	return NULL;
}

int main(){
	int i;
	char string[MAX_STRING_LENGTH];
	pthread_t threads[THREAD_COUNT];

	pthread_mutex_init(&mtx, NULL);

	for(i = 0; i < THREAD_COUNT; i++){
		printf("Insert string = ");
		fgets(string, MAX_STRING_LENGTH, stdin);
		pthread_create(&threads[i], NULL, processString, (void*)string);
		// this would have been used just to make the interface clearer
		//sleep(1);
	}

	for(i = 0; i < THREAD_COUNT; i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mtx);

	printf("Total number of vowels = %d\n", n);
	printf("Total number of digits = %d\n", v);

	return 0;
}
