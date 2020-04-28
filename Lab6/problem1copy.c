#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int p;

	p = fork();

	if (p == -1){
		printf("Error when forking");
		exit(1);
	}

	// child stuff
	if (p == 0){
		execlp("ls", "ls", "-l", NULL);
		exit(0);
	}

	// parent stuff
	else{
		wait(0);
	}

	return 0;
}
