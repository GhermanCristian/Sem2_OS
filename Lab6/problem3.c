#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv){
	int p, i;

	if (argc <= 1){
		printf("Invalid number of arguments\n");
		return 0;
	}

	for(i = 1; i < argc; i++){
		p = fork();
		if (p == 0){
			execlp("sed", "sed", "-i", "s/[0-9]*//g", argv[i], NULL);
			exit(0);
		}

		wait(0);
	}

	return 0;
}
