#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int p, i;

	p = fork();

	if (p == -1){
		perror("fork failed");
		exit(1);
	}

	// child only
	if (p == 0){
		for (i = 0; i < 10; i++){
			printf("Child: i=%d pid=%d, ppid=%d\n", i, getpid(), getppid());
		}
		exit(0);
		// commenting this out will print the last line twice, once for the
		// parent and once for the child (first the child, then the parent)
	}

	// parent only
	else{
		for(i = 0; i < 10; i++){
			printf("Parent: i=%d pid=%d ppid=%d\n", i, getpid(), getppid());
		}
		wait(0);
		// commenting this out does ??
		// in problem1, doing this => the program wouldn't stop
	}

	printf("Finished; pid=%d ppid=%d\n", getpid(), getppid());
	
	return 0;
}
