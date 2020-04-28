#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

int numberOfVowels(char* currentWord){
	int len = strlen(currentWord);
	int i;
	int nrVowels = 0;
	char* foundVowel;
	const char vowels[11] = "aeiouAEIOU";						
	for(i = 0; i < len; i++) {
		foundVowel = strchr(vowels, currentWord[i]);
		if (foundVowel != NULL){
			nrVowels++;
		}
	}

	return nrVowels;
}

int main(){
	int a2b;
	int i;
	int argc;
	int totalVowels = 0;
	char currentWord[50];

	a2b = open("a2b", O_RDONLY);
	if (read(a2b, &argc, sizeof(int)) <= 0){
		perror("error when reading");
		return 0;
	}

	for (i = 1; i < argc; i++){
		if (read(a2b, currentWord, sizeof(char*)) <= 0){
			break;
		}

		totalVowels += numberOfVowels(currentWord);
	}
	close(a2b);

	printf("Total number of vowels: %d\n", totalVowels);
	return 0;
}
