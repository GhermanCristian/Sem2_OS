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

int endingCondition(char* currentWord){
	return (currentWord[0] == '$');
}

int main(){
	int a2b, b2a;
	int totalVowels = 0;
	char currentWord[50];

	a2b = open("a2b", O_RDONLY);
	b2a = open("b2a", O_WRONLY);

	while(1){
		if (read(a2b, currentWord, sizeof(char*)) <= 0){
			break;
		}

		if (endingCondition(currentWord) == 1){
			break;
		}

		totalVowels += numberOfVowels(currentWord);
	}	
	close(a2b);
	write(b2a, &totalVowels, sizeof(int));
	close(b2a);
	return 0;
}
