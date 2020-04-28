#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int i; // iterator
	int sum = 0;

	// no arguments were passed
	if (argc == 1){
		printf("No arguments passed\nThe sum is 0\n");
		return 0;
	}

	// compute the sum of the numbers
	for (i = 1; i < argc; i++){
		sum += atoi(argv[i]);
	}

	// print the sum of the numbers
	printf("The sum is %d\n", sum);
	return 0;
}
