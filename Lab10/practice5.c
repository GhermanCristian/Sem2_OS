//Sa se scrie un program care sorteaza un sir folosind threaduri. Programul principal creeaza un thread T1 a carui sarcina este sortarea intregului sir. Acest thread, creaza la randul sau doua threaduri T2 si T3 a caror sarcina este sortarea celor doua jumatati ale sirului. Dupa ce threadurile T2 si T3 termina de sortat cele doua jumatati, threadul T1 interclaseaza jumatatile sirului pentru a obtine varianta sortata. Pentru sortarea celor doua jumatati ale sirului threadurile T2 si T3 vor aplica un mecanism similar. Programul va fi rulat pentru un sir cu cateva zeci de mii de elemente. La sfarsit va fi afisat timpul in care a fost sortat intregul sir.Se vor folosi, daca este cazul, variabile mutex si / sau variabile conditionale. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define ELEMENT_COUNT 10000

typedef struct ThreadSortArgument{
	int* array;
	int startPos;
	int endPos;
}ThreadSortArgument;

void* threadSortFunction(void* argument){
	ThreadSortArgument currentArgument = *(ThreadSortArgument*)(argument);
	int *array = currentArgument.array;
	int i, j;
	int aux;

	for(i = currentArgument.startPos; i < currentArgument.endPos - 1; i++){
		for(j = i + 1; j < currentArgument.endPos; j++){
			if(array[i] > array[j]){
				aux = array[i];
				array[i] = array[j];
				array[j] = aux;
			}	
		}
	}

	return NULL;
}

void* mainThreadFunction(void* argument){
	int* array = (int*)argument;
	int* temporaryArray = (int*)malloc(ELEMENT_COUNT * sizeof(int));
	int i;
	int i1 = 0, i2 = ELEMENT_COUNT / 2;
	int newPos = 0;
	pthread_t threads[2];
	ThreadSortArgument threadArgs[2];
	for(i = 0; i < 2; i++){
		threadArgs[i].array = array;
		threadArgs[i].startPos = (ELEMENT_COUNT / 2) * i;
		threadArgs[i].endPos = (ELEMENT_COUNT / 2) * (i + 1);
		pthread_create(&threads[i], NULL, threadSortFunction, (void*)&threadArgs[i]);
	}

	for(i = 0; i < 2; i++){
		pthread_join(threads[i], NULL);
	}

	while(i1 < ELEMENT_COUNT / 2 && i2 < ELEMENT_COUNT){
		if (array[i1] < array[i2]){
			temporaryArray[newPos++] = array[i1++];
		}
		else{
			temporaryArray[newPos++] = array[i2++];
		}
	}
	for(; i1 < ELEMENT_COUNT / 2; i1++){
		temporaryArray[newPos++] = array[i1];
	}
	for(; i2 < ELEMENT_COUNT; i2++){
		temporaryArray[newPos++] = array[i2];
	}
	for(i = 0; i < ELEMENT_COUNT; i++){
		array[i] = temporaryArray[i];
	}

	return NULL;
}

int main(){
	int i;
	int array[ELEMENT_COUNT];
	pthread_t mainThread;

	srand(time(NULL));
	for(i = 0; i < ELEMENT_COUNT; i++){
		array[i] = rand() % 1000;
	}
	pthread_create(&mainThread, NULL, mainThreadFunction, array);
	pthread_join(mainThread, NULL);

	return 0;
}
