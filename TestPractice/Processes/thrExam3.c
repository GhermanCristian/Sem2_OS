//Write a program that creates 7 threads and a global array of 10 integer 
//numbers, named SUM, storing the sum of numbers based on the remainder from 
//division with 10. Each thread generates random numbers between 0 and 100,
// and adds each number n to SUM[x], where x is n mod 10. The threads stop when
//  there have been exactly 5 numbers generated with the last digit 5. 
//  The main program prints the sums from the array SUM for each digit 
//  (print SUM[x]=nr  for each x=0..9, where nr is the sum of all numbers 
//  with remainder x from division by 10). Use efficient synchronisation 
//  mechanisms and print also the numbers that make up the sums.
//
//  Example:
//
//  ….
//  SUM[2]=12+22=34
//  SUM[3]=93=93
//  SUM[4]=84+24+64= 172

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define DIGIT_COUNT 10
#define THREAD_COUNT 7

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int sum[DIGIT_COUNT];
int numbersEndingInFive = 0;

void* generateNumbers(void* argument){
	while (1){
		pthread_mutex_lock(&mtx);
		if (numbersEndingInFive == 5){
			pthread_mutex_unlock(&mtx);
			break; // end condition
		}
		else{
			 pthread_mutex_unlock(&mtx);
		}
		
		int number = rand() % 101;
		int lastDigit = number % 10;
		pthread_mutex_lock(&mtx);
		if (lastDigit == 5){
			printf("generated number = %d\n", number);
			numbersEndingInFive++;
		}
		sum[lastDigit] += number;
		pthread_mutex_unlock(&mtx);
	}

	return NULL;
}

int main(){
	int i;
	pthread_t threads[THREAD_COUNT];
	srand(time(NULL));

	for(i = 0; i < THREAD_COUNT; i++){
		pthread_create(&threads[i], NULL, generateNumbers, NULL);
	}
	for(i = 0; i < THREAD_COUNT; i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mtx);

	for(i = 0; i < DIGIT_COUNT; i++){
		printf("sum[%d] = %d\n", i, sum[i]);
	}

	return 0;
}
