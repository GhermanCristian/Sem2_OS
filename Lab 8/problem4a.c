#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char** args){
	int a2b;
	int i;

	if (argc <= 1){
		perror("Not enough arguments");
		return 0;
	}

	a2b = open("a2b", O_WRONLY);
	write(a2b, &argc, sizeof(int));

	for (i = 1; i < argc; i++){
		write(a2b, args[i], sizeof(char*));
	}
	close(a2b);

	return 0;
}
