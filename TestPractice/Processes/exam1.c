// Sa se scrie un program care primeste o lista de parametrii din linia de comanda (minim 3). Parametrii pot contine litere, cifre sau simboluri.
// Programul are un tablou global "nr_aparitii", in care se vor calcula nr de aparitii ale fiecarei litere din alfabetul englez.
// Programul va crea cate un thread pentru fiecare parametru. Thread-ul parcurge parametrul respectiv si incrementeaza valoarea corespunzatoare din "nr_aparitii" pentru literele intalnite.
// Programul va afisa caracterul cu numarul maxim de aparitii (in toti parametrii liniei de comanda).
// Folositi mecanismele de sincronizare necesare pentru a asigura calcularea corecta a frecventelor.
// Validati numarul de parametrii ai liniei de comanda.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define TOTAL_LETTERS 26

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int letterCount[TOTAL_LETTERS];

void* parseWord(void* wordPointer){
	char* word = (char*)wordPointer;
	int len = strlen(word);
	int i;
	
	for(i = 0; i < len; i++){
		if (word[i] >= 'A' && word[i] <= 'Z'){
			word[i] -= 32; // change uppercase to lowercase
		}

		// all letters (including uppercase) will be here
		if (word[i] >= 'a' && word[i] <= 'z'){	
			pthread_mutex_lock(&mtx);
			letterCount[ word[i] - 'a' ]++;
			pthread_mutex_unlock(&mtx);
		}
	}

	return NULL;
}

int main(int argc, char** argv){
	int i;
	int maxCount = 0;
	char maxLetter;
	pthread_t threads[argc];

	if (argc <= 1){
		printf("Not enough arguments\n");
		return 0;
	}

	for(i = 1; i < argc; i++){
		pthread_create(&threads[i], NULL, parseWord, argv[i]);
	}
	for(i = 1; i < argc; i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mtx);

	for(i = 0; i < TOTAL_LETTERS; i++){
		if (letterCount[i] > maxCount){
			maxCount = letterCount[i];
			maxLetter = i + 'a';
		}
	}

	if (maxCount == 0){
		printf("No letters\n");
	}
	else{
		printf("Most encountered letter is %c (%d times)\n", maxLetter, maxCount);
	}
	return 0;
}
