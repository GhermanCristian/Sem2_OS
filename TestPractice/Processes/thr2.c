#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

typedef struct ThreadArgument{
	char fileName[100];
	int n;
}ThreadArgument;

void* threadFunction(void* argument){
	ThreadArgument currentArgument = *(ThreadArgument*)argument;
	int i; 
	char nthChar;
	FILE* fp = fopen(currentArgument.fileName, "r");
	// for now, we'll assume that the files are different, otherwise we might need a mutex
	for(i = 0; i < currentArgument.n; i++){
		nthChar = fgetc(fp);
		if (nthChar == EOF){
			printf("File %s is not long enough\n", currentArgument.fileName);
			break;
		}
	}
	if (nthChar != EOF){
		printf("File: %s; Char: '%c'\n", currentArgument.fileName, nthChar);
	}

	fclose(fp);
	return NULL;
}

int main(int argc, char** argv){
	int i;
	pthread_t threads[argc / 2 + 1];
	ThreadArgument threadArg[argc / 2 + 1];

	for(i = 1; i <= argc / 2; i++){
		strcpy(threadArg[i].fileName, argv[2 * i - 1]);
		threadArg[i].n = atoi(argv[2 * i]);
		pthread_create(&threads[i], NULL, threadFunction, (void*)&threadArg[i]);
	}
	for(i = 1; i <= argc / 2; i++){
		pthread_join(threads[i], NULL);
	}

	return 0;
}
