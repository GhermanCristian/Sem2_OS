// Sa se scrie un program care primeste o lista de parametrii in linia de comanda (max 10), care contin litere lowercase si caractere speciale. Programul afiseaza numarul total de vocale si nr total de consoane din acele mesaje. Programul va porni cate un thread pentru fiecare parametru, care va numara cele doua tipuri de caractere cautate: vocale si consoane din mesajul primit ca parametru. Programul afiseaza cele doua valori calculate. Codul trebuie sa complieze corect si sa fie indentat.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int vowelCount = 0;
int consonantCount = 0;

void* parseWord(void* wordPointer){
	char* word = (char*)wordPointer;
	int len = strlen(word);
	int i;
	
	for(i = 0; i < len; i++){
		if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')){	
			if (strchr("aeiouAEIOU", word[i]) != NULL){
				pthread_mutex_lock(&mtx);
				vowelCount++;
				pthread_mutex_unlock(&mtx);
			}
			else{
				pthread_mutex_lock(&mtx);
				consonantCount++;
				pthread_mutex_unlock(&mtx);
			}
		}
	}

	return NULL;
}

int main(int argc, char** argv){
	int i;
	pthread_t threads[argc];

	for(i = 1; i < argc; i++){
		pthread_create(&threads[i], NULL, parseWord, argv[i]);
	}
	for(i = 1; i < argc; i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mtx);

	printf("Vowels: %d\n", vowelCount);
	printf("Consonants: %d\n", consonantCount);

	return 0;
}
