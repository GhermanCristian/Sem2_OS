#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(){
	int p;
	int p2c[2]; // from parent (p1) to child (p2)
	char nthChar;
	int n;
	FILE* fp;
	int i;
	int a2b; // fifo

	pipe(p2c);
	p = fork();

	if (p < 0){
		printf("Error when forking\n");
		return 0;
	}
	if (p == 0){ // child <=> p2
		close(p2c[1]);
		read(p2c[0], &nthChar, sizeof(char));
		
		if (('a' <= nthChar && nthChar <= 'z') || ('A' <= nthChar && nthChar <= 'Z')){
			printf("it's a letter\n");
		}
		else if('0' <= nthChar && nthChar <= '9'){
			printf("it's a digit\n");
		}
		else{
			printf("it's not a letter nor a digit\n");
		}
		
		a2b = open("a2b", O_WRONLY);
		write(a2b, &nthChar, sizeof(char));
		close(a2b);

		exit(0);
	}
	else{ // parent <=> p1
		close(p2c[0]);

		printf("n = "); scanf("%d", &n);
		fp = fopen("data.txt", "r");	
		for(i = 0; i < n; i++){
			nthChar = fgetc(fp);
		}
		write(p2c[1], &nthChar, sizeof(char));
		fclose(fp);
		wait(0);
	}

	return 0;
}

