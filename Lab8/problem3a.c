#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int endingCondition(char* currentWord){
	return (currentWord[0] == '$');
}

int main(){
	int a2b, b2a;
	int totalVowels;
	char currentWord[50];
	//char* a2bString = "a2b";
	//char* b2aString = "b2a";

	//mkfifo(a2bString, 777);
	//mkfifo(b2aString, 777);
	//mkfifo("a2b", 666);
	//mkfifo("b2a", 666);
	//if (mkfifo("a2b", 666) != 0){
	//	printf("Error when creating fifo.");
	//}
	//if (mkfifo("b2a", 666) != 0){
	//	printf("Error when creating fifo.");
	//}
	
	a2b = open("a2b", O_WRONLY);
	b2a = open("b2a", O_RDONLY);
	printf("Before while");
	while(1){
		printf("\nInsert word: ");
		scanf("%s", currentWord);
		printf("Current word: %s", currentWord);		
		if (endingCondition(currentWord) == 1){
			break;
		}

		write(a2b, currentWord, sizeof(char*));
	}

	close(a2b);
	read(b2a, &totalVowels, sizeof(int));
	close(b2a);
	
	//remove("a2b");
	//remove("b2a");

	printf("Total number of vowels: %d\n", totalVowels);
	return 0;
}
