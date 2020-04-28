/* RO: Rezolvati problemele compilare (erori si warning-uri)
 * si rulare, incat programul sa citeasca de la tastatura elementele
 * unei matrice si sa le calculeze suma.
 *
 * EN: Fix the compilation errors/warnings and the runtime problems, so that
 * the program will read the elements of a matrix and compute their sum.
 */
#include <stdio.h>
#include <stdlib.h>

int main() {
    // declare and preinit variables
    int l = 0;
    int c = 0;
    int i = 0;
    int j = 0;
    int sum = 0;
    int **matr;

    // read no of lines and no of columns
    printf("l=");
    scanf("%d", &l);

    printf("c=");
    scanf("%d", &c);

    // allocate matrix
    matr = (int**)malloc(l * sizeof(int*));

    for (i = 0; i < l; i++)
    {
        matr[i] = (int*)malloc(c * sizeof(int));
    }

    // read elements
    for (i = 0; i < l; i++)
    {
        for (j = 0; j < c; j++)
        {
            printf("m[%d][%d]=", i, j);
            scanf("%d", &matr[i][j]);
        }
    }

    // compute sum of all elements
    sum = 0;
    for (i = 0; i < l; i++)
    {
        for (j = 0; j < c; j++)
        {
            sum += matr[i][j];
        }
    }

    printf("Sum = %d\n", sum);

    for (i = 0; i < l; i++){
    	free(matr[i]);
    }
    free(matr);

    return 0;
}
