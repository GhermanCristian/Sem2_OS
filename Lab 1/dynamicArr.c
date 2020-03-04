#include <stdio.h>
#include <stdlib.h>

int main(){
	int i; //iterator
	int nrElem;
	int *arr;

	// read the number of elements
	printf("Insert the number of elements: ");
	scanf("%d", &nrElem);

	// allocate memory for the array
	arr = (int*)malloc(nrElem * sizeof(int));

	// check the success of the allocation
	if (arr == NULL){
		printf("malloc failed\n");
		return 0;
	}

	// read the elements of the array
	for(i = 0; i < nrElem; i++){
		printf("arr[%d] = ", i);
		scanf("%d", &arr[i]);
	}

	// display the elements of the array
	printf("The elements of the array are:\n");
	for (i = 0; i < nrElem; i++){
		printf("arr[%d] = %d\n", i, arr[i]);
	}
	printf("\n");

	// deallocate memory
	free(arr);

	return 0;
}
