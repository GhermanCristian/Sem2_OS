#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(){
	int p, nrCommands = 0, i;
	char command[100];
	char** args;
	args = (char**)malloc(5 * sizeof(char*));

	if (args == NULL){
		return 0;
	}
	printf("Successful arr of arr allocation\n");

	while (1){
		fgets(command, 100, stdin); 
		
		p = fork();

		if (p == -1){
			printf("Error when forking");
			exit(1);
		}
	
		// child stuff
		if (p == 0){
			printf("the command is: %s", command);

			args[nrCommands] = strtok(command, " ");
			while(args[nrCommands] != NULL){
				args[++nrCommands] = strtok(NULL, " ");
			}

			for (i = 0; i < nrCommands; i++){
				printf("arg%d: %s\n", i, args[i]);
			}

			args[nrCommands - 1][strlen(args[nrCommands - 1]) - 1] = '\0';
			execvp(args[0], args);
			exit(0);
		}
		
		// parent stuff
		else{
			wait(0);
			
			free(args);
			
			exit(0); // i only do one execution for now
		}
	}

	return 0;
}
