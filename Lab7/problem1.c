#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int isPrime(int x){
	if (x <= 1){
		return 0;
	}
	int d;
	for(d = 2; d * d <= x; d++){
		if (x % d == 0){
			return 0;
		}
	}

	return 1;
}

int main(){
	int parentToChild[2];
	int number;
	int p;

	pipe(parentToChild);
	p = fork();

	if (p == -1){
		perror("Error when forking\n");
		exit(0);
	}

	else if (p == 0){
		// child
		close(parentToChild[1]); // the child doesn't write anything
		
		while(1){
			// read is unsuccessful
			if (read(parentToChild[0], &number, sizeof(int)) <= 0){
				break;	
			}
			// end condition
                        if (number == 0){
				 break;
			}

			if (isPrime(number) == 1){
				printf("Number = %d is prime\n", number);
			}
			else{
				printf("Number = %d is not prime\n", number);
			}
		}
		
		close(parentToChild[0]);
		exit(0);
	}

	else{
		// parent
		close(parentToChild[0]); // the parent doesn't read anything
		do{
			printf("Insert number: \n");
			scanf("%d", &number);
			write(parentToChild[1], &number, sizeof(int));
		}while(number != 0);
		close(parentToChild[1]);
		wait(0);
	}

	return 0;
}
