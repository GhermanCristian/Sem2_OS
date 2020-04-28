#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int endingCondition(char* currentWord){
	return (currentWord[0] == '$');
}

int main(){
	int a2b, b2a;
	int totalVowels;
	char currentWord[50];
	a2b = open("a2b", O_WRONLY);
	b2a = open("b2a", O_RDONLY);

	while(1){
		printf("\nInsert word: ");
		scanf("%s", currentWord);
		
		if (endingCondition(currentWord) == 1){
			break;
		}

		write(a2b, currentWord, sizeof(char*));
	}

	close(a2b);
	read(b2a, &totalVowels, sizeof(int));
	close(b2a);
	
	printf("Total number of vowels: %d\n", totalVowels);
	return 0;
}
