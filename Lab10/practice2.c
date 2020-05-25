//Sa se scrie un program care primeste o lista de parametrii din linia de comanda (minim 5). Fiecare parametru reprezinta un numar natural.
//Programul citeste de la tastatura 3 numere naturale (x, y, z) si are un tablou global "nr_divizori", corespunzand celor 3 numere citite de la tastatura.
//Programul va porni cate un thread penru fiecare parametru din linia de comanda. Fiecare thread va determina daca parametrul primit este divizor pentru cele 3 numere citite. Daca parametrul curent este divizor pentru unul din cele 3 numere, se va incrementa nr de divizori ai acelui numar.
//Programul va afisa numarul cu cei mai multi divizori (in toti parametrii liniei de comanda).
//Folositi mecanismele de sincronizare necesare pentru a asigura calcularea corecta a divizorilor.
//Validati numarul de parametrii ai liniei de comanda.
//Ex: 2 3 5 7 13
//x = 105; y = 6; z = 2
//Se va afisa 105 (deoarece x are 3 divizori; y are 2; z are 1)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int x, y, z;
int divisorCount[3];
pthread_mutex_t mtx;

void* countDivisors(void* numberAsString){
	int number = atoi(numberAsString);

	// normally I would have a for and lock/unlock just around the ++ instruction
	// but now I'm too lazy for that
	pthread_mutex_lock(&mtx);
	if (x % number == 0){
		divisorCount[0]++;
	}
	if (y % number == 0){
		divisorCount[1]++;
	}
	if (z % number == 0){
		divisorCount[2]++;
	}
	pthread_mutex_unlock(&mtx);

	return NULL;
}

int main(int argc, char** argv){
	int i;
	int maxValue = 0;
	int maxIndex;
	int printedValue;
	pthread_t threads[argc];
	printf("x = ");scanf("%d", &x);
	printf("y = ");scanf("%d", &y);
	printf("z = ");scanf("%d", &z);
	pthread_mutex_init(&mtx, NULL);
	
	for(i = 1; i < argc; i++){
		pthread_create(&threads[i], NULL, countDivisors, argv[i]);
	}
	for(i = 1; i < argc; i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mtx);

	for(i = 0; i < 3; i++){
		if (divisorCount[i] > maxValue){
			maxValue = divisorCount[i];
			maxIndex = i;
		}
	}
	if (maxIndex == 0){
		printedValue = x;
	}
	else if (maxIndex == 1){
		printedValue = y;
	}
	else{
		printedValue = z;
	}
	printf("%d\n", printedValue);

	return 0;
}
