#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(){
	int a2b;
	char nthChar;

	a2b = open("a2b", O_RDONLY);
	read(a2b, &nthChar, sizeof(char));
	close(a2b);

	printf("ascii code = %d\n", nthChar);

	return 0;
}
