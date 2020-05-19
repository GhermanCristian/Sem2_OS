#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int main(){
	int a2b;
	int b2a;
	int number;
	int totalSum;

	a2b = open("a2b", O_WRONLY);
	b2a = open("b2a", O_RDONLY);

	do{
		printf("Insert number = ");
		scanf("%d", &number);
		write(a2b, &number, sizeof(int));
	}while(number != 0);

	close(a2b);
	read(b2a, &totalSum, sizeof(int));
	close(b2a);

	printf("Total sum = %d\n", totalSum);
	return 0;
}
