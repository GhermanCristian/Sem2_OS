//Se se implementeze doua procese A si B. Procesul A citeste de la tastatura numere < 1000, pana la intalnirea valorii 0 si i le transmite procesului B. B verifica care dintre acele numere este scris cu o singura cifra (ex: 7, 77, 777), calculeaza suma acelor numere si o transmite procesului A. A afiseaza suma calculata de B. Codul C trebuie sa compileze fara erori sau warning-uri si sa fie indentat.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

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
	int p2c[2];
	int c2p[2];
	int p;
	int number;
	int numberSum;

	pipe(p2c);
	pipe(c2p);

	p = fork();

	if (p < 0){
		printf("Error when forking");
		return 0;
	}
	if (p == 0){
		// child stuff
		close(p2c[1]);
		close(c2p[0]);
		numberSum = 0;
		
		while (1){
			if (read(p2c[0], &number, sizeof(int)) <= 0){
				break;
			}
			if (number == 0){
				break;
			}
			if (hasOneDigit(number) == 1){
				numberSum += number;	
			}
		}
		write(c2p[1], &numberSum, sizeof(int));

		close(p2c[0]);
		close(c2p[1]);
		exit(0);
	}
	else{
		// parent stuff
		close(p2c[0]);
		close(c2p[1]);
		
		do{
			printf("Insert number = ");
			scanf("%d", &number);
			write(p2c[1], &number, sizeof(int));
		}while(number != 0);

		close(p2c[1]);
		wait(0);
		read(c2p[0], &numberSum, sizeof(int));
		printf("Total sum = %d\n", numberSum);
		close(c2p[0]);
	}

	return 0;
}
