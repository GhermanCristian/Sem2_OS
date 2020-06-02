#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define INITIAL_LETTERS 5

int numberOfWords = 0;
pthread_mutex_t mtx;

void* processWord(void* argument){
	char* word = (char*)argument;
	int len = strlen(word);
	int i;
	int found = 0;

	for(i = 0; i < len; i++){
		if (strchr("abcdeABCCDE", word[i]) != NULL){
			found = 1;
		} 
	}

	if (found == 1){
		pthread_mutex_lock(&mtx);
		numberOfWords++;
		pthread_mutex_unlock(&mtx);
	}

	return NULL;
}

int main(int argc, char** argv){
	int i;
	pthread_t threads[argc];
	pthread_mutex_init(&mtx, NULL);

	for(i = 1; i < argc; i++){
		pthread_create(&threads[i], NULL, processWord, (void*)argv[i]);
	}
	for(i = 1; i < argc; i++){
		pthread_join(threads[i], NULL);
	}
	pthread_mutex_destroy(&mtx);

	printf("Number of words with the letters are: %d\n", numberOfWords);

	return 0;
}

