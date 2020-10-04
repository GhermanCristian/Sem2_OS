//Sa se scrie un program care citeste un nr N de la tastatura, si creeaza 2 threaduri (pot fi descrise de doua functii diferite, sau de aceeasi functie). Unul dintre ele va genera un numar par aleator pe care sa il adauge intr-un sir primit ca parametru de la threadul principal, iar celalalt va face acelasi lucru, generand in schimb numere impare. Intre cele 2 threaduri trebuie implementata o sincronizare care sa asigure ca in sir se adauga alternativ cate un numar par, respectiv impar, pana la lungimea maxima N. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtxEven = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtxOdd = PTHREAD_MUTEX_INITIALIZER;
int currentLength = 0;
int n;

void* generateEvenNumber(void* list){
	pthread_mutex_lock(&mtxOdd);
	while (currentLength < n){
		((int*)list)[currentLength] = (rand() % 20) * 2;
		currentLength++;
		//pthread_mutex_unlock(&mtxOdd);
		pthread_mutex_lock(&mtxEven);
		pthread_mutex_unlock(&mtxOdd);
	}

	return NULL;
}
void* generateOddNumber(void* list){
	while(currentLength < n){
		((int*)list)[currentLength] = (rand() % 20) * 2 + 1;
		currentLength++;
		pthread_mutex_lock(&mtxOdd);
		pthread_mutex_unlock(&mtxEven);
	}
	pthread_mutex_unlock(&mtxOdd);
	return NULL;
}

int main(){
	int* array;
	int i;
	pthread_t threads[2];

	srand(time(NULL));
	printf("n = ");
	scanf("%d", &n);
	array = (int*)malloc(n * sizeof(int));

	pthread_create(&threads[0], NULL, generateEvenNumber, array);
	pthread_create(&threads[1], NULL, generateOddNumber, array);
	
	for(i = 0; i < 2; i++){
		pthread_join(threads[i], NULL);
	}

	for(i = 0; i < n; i++){
		printf("%d ", array[i]);
	}
	printf("\n");

	free(array);
	pthread_mutex_destroy(&mtx);
	return 0;
}
