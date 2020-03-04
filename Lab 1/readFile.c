#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int i, j; // iterators
	int rows, columns;
	int **matrix;
	int *columnSum;
	FILE *f;

	if (argc == 1){
		printf("No arguments passed\n");
		return 0;
	}

	f = fopen(argv[1], "r");

	if (f == NULL){
		printf("Cannot open the file.");
		return 0;
	}
	fscanf(f, "%d %d", &rows, &columns);

	// allocate the memory
	matrix = (int **)malloc(rows * sizeof(int *));
	for (i = 0; i < rows; i++){
		matrix[i] = (int*)malloc(columns * sizeof(int));
	}
	columnSum = (int *)malloc(columns * sizeof(int));
	for (j = 0; j < columns; j++){
		columnSum[j] = 0;
	}

	// read the elements of the matrix
	for (i = 0; i < rows; i++){
		for (j = 0; j < columns; j++){
			fscanf(f, "%d", &matrix[i][j]);
			columnSum[j] += matrix[i][j];
		}
	}

	// display the matrix on the screen
	for (i = 0; i < rows; i++){
		for (j = 0; j < columns; j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	printf("The sums on the columns:\n");
	// display the array of sums
	for (j = 0; j < columns; j++){
		printf("%d ", columnSum[j]);
	}
	printf("\n");

	// free the memory
	for (i = 0; i < rows; i++){
		free (matrix[i]);
	}
	free (matrix);
	free (columnSum);

	// close the file
	fclose(f);

	return 0;
}
