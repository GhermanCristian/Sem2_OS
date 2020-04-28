//!!!!!	POATE NU LUATI 10 !!!!!
////Se citeste o matrice dintr-un fisier dat ca parametru din linie de comanda.
////Fisierul respectiv contine pe prima linie dimensiunile matricii (numarul de linii si coloane)
////iar pe urmatoarele liniii matricea. Atat matricea cat si dimensiunile sale se
////stocheaza intr-o structura de tip array alocata dinamic in memorie.
////sa se afiseze pe ecran sumele elementelor de pe fiecare linie a matricii.
////ex:
////input
////3 4
////1 2 3 4
////9 6 7 8
////2 4 4 4
////output
////10 
////30
////14 

#include <stdio.h>
#include <stdlib.h>

int main(int argv, char **args){
	int rows, columns;
	int **matrix;
	int i, j; // iterators
	int sum;
	FILE *file;

	if (argv == 1){
		printf("Not enough parameters\n");
		return 0;
	}

	file = fopen(args[1], "r");
	if (file == NULL){
		printf("Couldn't open the file\n");
		return 0;
	}

	fscanf(file, "%d %d", &rows, &columns);
	matrix = (int **)malloc(rows * sizeof(int *));
	for(i = 0; i < rows; i++){
		matrix[i] = (int *)malloc(columns * sizeof(int));
	}

	for(i = 0; i < rows; i++){
		sum = 0;
		for(j = 0; j < columns;j++){
			fscanf(file, "%d", &matrix[i][j]);
			sum += matrix[i][j];
		}
		printf("sum = %d\n", sum);
	}

	fclose(file);
	for(i = 0; i < rows; i++){
		free(matrix[i]);
	}
	free(matrix);

}
