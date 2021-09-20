#include <stdio.h>
#include <stdlib.h>

//Determinant
//Calculation by the first line

int** matrix_alloc(int N);
void matrix_free(int **A, int N);
int det(int **A, int N);
void submatrix(int **A, int N, int **B, int k);

int main()
{
    int N, i, j, **A = NULL;
    scanf("%d", &N);
    A = matrix_alloc(N);
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            scanf("%d", &A[i][j]);
    printf("%d\n", det(A, N));
    matrix_free(A, N);
    return 0;
}

int** matrix_alloc(int N)
{
    int **A = NULL, i;
    A = malloc(N * sizeof(int*));
    for(i = 0; i < N; i++)
        A[i] = (int*)malloc(N * sizeof(int));
    return A;
}

void matrix_free(int **A, int N)
{
    int i;
    for (i = 0; i < N; i++)
        free(A[i]);
    free(A);
}

int det(int **A, int N)
{
    int i, d = 0, sign = 1, **B = NULL;
    if (N == 1)
        return A[0][0];
    B = matrix_alloc(N - 1);
    for(i = 0; i < N; i++)
    {
        submatrix(A, N, B, i);
        d += sign*A[0][i]*det(B, N - 1);
        sign = -sign;
    }
    matrix_free(B, N - 1);
    return d;
}

//delete first line and kth column
//N is size of A
void submatrix(int **A, int N, int **B, int k)
{
    int i, j;
    for(i = 1; i < N; i++)
    {
        for(j = 0; j < k; j++)
            B[i - 1][j] = A[i][j];
        for(j = k + 1; j < N; j++)
            B[i - 1][j - 1] = A[i][j];
    }
}
