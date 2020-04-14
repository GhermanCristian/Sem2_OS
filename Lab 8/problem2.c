//Write a program that creates a child process. The parent reads words (from the console) and sends them to the child. The child process computes the total number of vowels in those words. The parent stops reading words when it reads "$" and then displays the total number of vowels computed by the child. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

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
	int parentToChild[2];
	int childToParent[2];
	int p;
	char currentWord[50];
	int foundEnd;
	int totalVowels;

	pipe(parentToChild);
	pipe(childToParent);
	p = fork();

	if (p < 0){
		perror("Error when forking");
		exit(0);
	}

	if (p == 0){
		// child stuff
		// close unused pipes
		close(childToParent[0]);
		close(parentToChild[1]);
		totalVowels = 0;

		while(1){
			if (read(parentToChild[0], &currentWord, sizeof(char*)) <= 0){
				break;
			}

			if (endingCondition(currentWord) == 1){
				break;
			}

			totalVowels += numberOfVowels(currentWord);
		}
		close(parentToChild[0]);

		write(childToParent[1], &totalVowels, sizeof(int));
		close(childToParent[1]);
		exit(0);
	}

	else{
		// parent stuff
		// close unused pipes
		close(parentToChild[0]);
		close(childToParent[1]);

		foundEnd = 0;
		
		while (foundEnd == 0){
			printf("\nInsert word: ");
			scanf("%s", currentWord);
			if (endingCondition(currentWord) == 1){
				foundEnd = 1;
			}
			else{
				write(parentToChild[1], &currentWord, sizeof(char*));
			}
		}

		close(parentToChild[1]);
		wait(0);

		read(childToParent[0], &totalVowels, sizeof(int));
		printf("Total number of vowels: %d\n", totalVowels);
		close(childToParent[0]);
	}

	return 0;
}
