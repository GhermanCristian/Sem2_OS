#include <stdio.h>
#include <stdlib.h>

const int MAX_LENGTH = 101;

int main(){
	int nrRows;
	int nrColumns;
	int **matrix;
	int i, j; // iterators

	printf("Insert the nr of rows and the nr of columns:\n");
	scanf("%d %d", &nrRows, &nrColumns);

	// allocate memory for the matrix
	matrix = (int **)malloc(nrRows * sizeof(int*));
	for(i = 0; i < nrRows; i++){
		matrix[i] = (int *)malloc(nrColumns * sizeof(int));
	}

	// read the elements of the matrix
	for(i = 0; i < nrRows; i++){
		for(j = 0; j < nrColumns; j++){
			printf("matrix[%d][%d] = ", i, j);
			scanf("%d", &matrix[i][j]);	
		}		

	}

	// display the elements of the matrix
	for(i = 0; i < nrRows; i++){
		for(j = 0; j < nrColumns; j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	// free the memory
	for(i = 0; i < nrRows; i++){
		free(matrix[i]);
	}
	free(matrix);
}
