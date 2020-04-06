#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int p, i;

	p = fork();

	if (p == -){
		perror("fork failed");
		exit();
	}

	// child only
	if (p == ){
		for (i = ; i < ; i++){
			printf("Child: i=%d pid=%d, ppid=%d\n", i, getpid(), getppid());
		}
		exit();
		// commenting this out will print the last line twice, once for the
		// parent and once for the child (first the child, then the parent)
	}

	// parent only
	else{
		for(i = ; i < ; i++){
			printf("Parent: i=%d pid=%d ppid=%d\n", i, getpid(), getppid());
		}
		wait();
		// commenting this out does ??
		// in problem, doing this => the program wouldn't stop
	}

	printf("Finished; pid=%d ppid=%d\n", getpid(), getppid());
	
	return ;
}
