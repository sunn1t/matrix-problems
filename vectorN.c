#include <stdio.h>
#include <stdlib.h>

int** matrix_alloc(int M, int N);
void submatrix(int **A, int M, int N, int **B, unsigned k, unsigned p);
int det(int **A, int N);
void matrix_free(int **A, int M);

int main()
{
    int **A, **B, res, sign = 1;
    unsigned N, i, j;
    scanf("%d", &N);
    A = matrix_alloc(N, N + 1);
    B = matrix_alloc(N, N);
    for(i = 0; i < N; i++)
        for(j = 0; j < N + 1; j++)
            scanf("%d", &A[i][j]);
    for(i = 0; i < N + 1; i++)
    {
        submatrix(A, N, N + 1, B, i, -1);
        res = sign*det(B, N);
        sign = -sign;
        printf("%d ", res);
    }
    printf("\n");
    matrix_free(A, N);
    matrix_free(B, N);
    return 0;
}

int** matrix_alloc(int M, int N)
{
    int **A = (int**)malloc(M*sizeof(int*));
    int i;
    for(i = 0; i < M; i++)
        A[i] = (int*)malloc(N*sizeof(int));
    return A;
}

/*delete kth column and pth line: result -> B*/
void submatrix(int **A, int M, int N, int **B, unsigned k, unsigned p)
{
    int i, j;
    k = k > N ? N : k;
    p = p > M ? M : p;
    for(i = 0; i < p; i++)
    {
        for(j = 0; j < k; j++)
            B[i][j] = A[i][j];
        for(j = k + 1; j < N; j++)
            B[i][j - 1] = A[i][j];
    }
    for(i = p + 1; i < M; i++)
    {
        for(j = 0; j < k; j++)
            B[i - 1][j] = A[i][j];
        for(j = k + 1; j < N; j++)
            B[i - 1][j - 1] = A[i][j];
    }
}

int det(int **A, int N)
{
    int i, d = 0, sign = 1, **B = NULL;
    if (N == 1)
        return A[0][0];
    B = matrix_alloc(N - 1, N - 1);
    for(i = 0; i < N; i++)
    {
        submatrix(A, N, N, B, i, 0);
        d += sign*A[0][i]*det(B, N - 1);
        sign = -sign;
    }
    matrix_free(B, N - 1);
    return d;
}

void matrix_free(int **A, int M)
{
    int i;
    for(i = 0; i < M; i++)
        free(A[i]);
    free(A);
}

