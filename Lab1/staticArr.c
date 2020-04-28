#include <stdio.h>

const int MAX_LEN = 101;

int main(){
	int i; //iterator
	int nrElem;
	int arr[MAX_LEN];
	int maxElem = -100, minElem = 100;
	double sum = 0, average;

	printf("Insert the number of elements: ");
	scanf("%d", &nrElem);

	if (nrElem > MAX_LEN){
		printf("Too many elements");
		return 0;
	}

	for (i = 0; i < nrElem; i++){
		printf("arr[%d] = ", i);
		scanf("%d", &arr[i]);
		if (maxElem < arr[i]){
			maxElem = arr[i];
		}
		if (minElem > arr[i]){
			minElem = arr[i];
		}
		sum += (double)(arr[i]);
	}
	average = sum / (double)(nrElem);
	printf("The array is:\n");

	for (i = 0; i < nrElem; i++){
		printf("arr[%d] = %d\n", i, arr[i]);
	}

	printf("The max value is: %d\n", maxElem);
	printf("The min value is: %d\n", minElem);
	printf("The average value is: %.2f\n", average);

	return 0;
}
