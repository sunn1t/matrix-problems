#include <stdio.h>
#include <stdlib.h>

#define cor0(x) ((x) > -1e-10 && (x) < 1e-10 ? 0 : (x))

//Determinant
//Gauss method

double** matrix_alloc(int N);
void matrix_free(double **A, int N);
double Gauss_det(double **A, int N);
int find_not_zero(double **A, int N, int column);
void swap_lines(double **A, int p, int r);

int main()
{
    int N, i, j;
    double **A = NULL;
    scanf("%d", &N);
    A = matrix_alloc(N);
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            scanf("%lf", &A[i][j]);
    printf("%lg\n", Gauss_det(A, N));
    matrix_free(A, N);
    return 0;
}

double **matrix_alloc(int N)
{
    double **A = (double**)malloc(N * sizeof(double*));
    int i;
    for(i = 0; i < N; i++)
        A[i] = (double*)malloc(N * sizeof(double));
    return A;
}

void matrix_free(double **A, int N)
{
    int i;
    for (i = 0; i < N; i++)
        free(A[i]);
    free(A);
}

double Gauss_det(double **A, int N)
{
    int i, j, k;
    double res = 1;
    for(k = 0; k < N; k++)
        if ((i = find_not_zero(A, N, k)) != -1)
        {
            if (i != k)
            {
                swap_lines(A, i, k);
                res = -res;
            }
            res *= A[k][k];
            for(j = N - 1; j >= k; j--)
                A[k][j] /= A[k][k];
            for(i = k + 1; i < N; i++)
                for(j = N - 1; j >= k; j--)
                    A[i][j] -= A[k][j]*A[i][k];
        }
        else
            return 0;
    return res;
}

int find_not_zero(double **A, int N, int column) //find 1st nonzero number in the column
{
    int i;
    for (i = column; i < N; i++)
        if (cor0(A[i][column]))
            return i;
    return -1;
}

void swap_lines(double **A, int p, int r)
{
    double *tmp = A[p];
    A[p] = A[r];
    A[r] = tmp;
}
