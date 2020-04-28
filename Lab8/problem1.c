// Write a program that creates a child process. The parent reads a number (from the console) and sends it to the child. The child checks if that number is even or odd and displays a message.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int parentToChild[2];
	int p;
	int number;

	pipe(parentToChild);
	p = fork();

	if (p < 0){
		perror("Error when forking");
		exit(0);
	}
	// child code
	if (p == 0){
		close(parentToChild[1]); // the child doesn't write to the pipe
		read(parentToChild[0], &number, sizeof(int));

		if (number % 2 == 0){
			printf("Number is even\n");
		}
		if (number % 2 == 1){
			printf("Number is odd\n");
		}

		close(parentToChild[0]);
		exit(0);
	}
	// parent code
	else{
		close(parentToChild[0]); // the parent doesn't read from the pipe

		printf("Insert number: ");
		scanf("%d", &number);

		write(parentToChild[1], &number, sizeof(int));
		close(parentToChild[1]);
		wait(0);
	}

	return 0;
}
