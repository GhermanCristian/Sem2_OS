#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_LEN = 21;

int* sort(char **strings, int nrStrings){
	int n = nrStrings; // for ease of use
	int i; // iterator
	int *indexArr = (int*)malloc(n * sizeof(int));
	int aux;
	int sorted = 0;

	// initialise the array of indices
	for (i = 0; i < n; i++){
		indexArr[i] = i;
	}

	// bubblesort, but we use (and swap) just the array of indices
	while (sorted == 0){
		sorted = 1;
		for (i = 0; i < n-1; i++){
			if (strcmp(strings[indexArr[i]], strings[indexArr[i + 1]]) > 0){
				aux = indexArr[i];
				indexArr[i] = indexArr[i + 1];
				indexArr[i + 1] = aux;
				sorted = 0;		
			}
		}
	}

	return indexArr;
}

int main(){
	int nrStrings;
	int i; // iterator
	int *indexArr;
	char **strings;
	
	// read the nr of strings from the keyboard
	printf("Please insert the number of strings: \n");
	scanf("%d", &nrStrings);

	// initialize the strings
	// i am not 100% sure why, but i need to add 1 to nrStrings
	nrStrings ++;
	strings = (char**)malloc(nrStrings * sizeof(char*));
	for (i = 0; i < nrStrings; i++){
		strings[i] = (char*)malloc(MAX_LEN * sizeof(char));
	}

	// read the strings
	for (i = 0; i < nrStrings; i++){
		if (fgets (strings[i], MAX_LEN, stdin) == NULL){
			printf("Error when reading the strings");
			return 0;
		}
	}

	indexArr = sort(strings, nrStrings);

	// print the strings
	for (i = 0; i < nrStrings; i++){
		printf("%s", strings[indexArr[i]]);
	}
	
	// free the memory
	for (i = 0; i < nrStrings; i++){
		free(strings[i]);
	}
	free(strings);
	free(indexArr);

	return 0;
}
