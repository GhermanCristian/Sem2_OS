#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int hasOneDigit(int number){
	int digit = number % 10;
	while (number > 0){
		if (number % 10 != digit){
			return 0;
		}
		number /= 10;
	}
	return 1;
}

int main(){
	int a2b;
	int b2a;
	int number;
	int totalSum;

	a2b = open("a2b", O_RDONLY);
	b2a = open("b2a", O_WRONLY);

	totalSum = 0;
	while(1){
		if (read(a2b, &number, sizeof(int)) <= 0){
			break;
		}
		if (number == 0){
			break;
		}
		
		if (hasOneDigit(number) == 1){
			totalSum += number;
		}
	}
	close(a2b);
	write(b2a, &totalSum, sizeof(int));
	close(b2a);

	return 0;
}
