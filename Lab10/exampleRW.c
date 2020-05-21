//Sunt 1000 de oameni care verifica pretul unor bilete de avion si 10 oameni care cumpara. Pretul se calculeaza in functie de nr de locuri, dupa formula: pret = pret_baza * (2-nr_locuri/100) (sper ca sunt 100 locuri in total - dap).
//Un program care creaza 1000 de thread-uri care verifica pretul (readers) si 10 thread-uri care "cumpara" bilete, modificand astfel pretul (writers).

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define READER_COUNT 1000
#define WRITER_COUNT 10

int seats = 100;
double price = 75.0;
pthread_rwlock_t rwl;

void* checkSeats(void* currentClient){
	pthread_rwlock_rdlock(&rwl);
	printf("Reader: %d\nAvailable seats: %d\nPrice: %f\n", *(int*)currentClient, seats, price * (2 - seats / 100.0f));
	pthread_rwlock_unlock(&rwl);
	return NULL;
}

void* purchaseTicket(void* currentClient){
	pthread_rwlock_wrlock(&rwl);
	printf("Buyer: %d\nSeat: %d\nPrice: %f\n", *(int*)currentClient, seats, price * (2 - seats / 100.0f));
	seats--;
	pthread_rwlock_unlock(&rwl);
	return NULL;
}

int main(){
	pthread_t readerThreads[READER_COUNT];
	pthread_t writerThreads[WRITER_COUNT];
	int i;

	pthread_rwlock_init(&rwl, NULL);

	for(i = 0; i < READER_COUNT; i++){
		pthread_create(&readerThreads[i], NULL, checkSeats, (void*)&i);
	}
	for(i = 0; i < WRITER_COUNT; i++){
		pthread_create(&writerThreads[i], NULL, purchaseTicket, (void*)&i);
	}

	for(i = 0; i < READER_COUNT; i++){
		pthread_join(readerThreads[i], NULL);
	}
	for(i = 0; i < WRITER_COUNT; i++){
		pthread_join(writerThreads[i], NULL);
	}

	pthread_rwlock_destroy(&rwl);
}
