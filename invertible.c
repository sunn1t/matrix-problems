#include <stdio.h>
#include <stdlib.h>

#define cor0(x) ((x) > -1e-10 && (x) < 1e-10 ? 0 : (x))

//Inverse matrix
//Gauss method

double** matrix_alloc(int N);
void matrix_free(double **A, int N);
int Gauss1(double **A, int N);
void Gauss2(double **A, int N);
int find_not_zero(double **A, int N, int column);
void swap_lines(double **A, int p, int r);
void printmatrix(double **A, int N);

int main()
{
    int N, i, j;
    double **A;
    scanf("%d", &N);
    A = matrix_alloc(N);
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            scanf("%lf", &A[i][j]);
    printmatrix(A, N);
    if (Gauss1(A, N))
    {
        Gauss2(A, N);
        for(i = 0; i < N; i++)
        {
            for(j = 0; j < N; j++)
                printf("%lg ", cor0(A[i][N + j]));
            printf("\n");
        }
        printf("\n");
    }
    else
        puts("NO");
    matrix_free(A, N);
    return 0;
}

double** matrix_alloc(int N)
{
    double **A = (double**)malloc(N*sizeof(double*));
    int i;
    for(i = 0; i < N; i++)
    {
        int M = 2*N;
        A[i] = (double*)calloc(M, sizeof(double));
        A[i][N + i] = 1;
    }
    return A;
}

void matrix_free(double **A, int N)
{
    int i;
    for (i = 0; i < N; i++)
        free(A[i]);
    free(A);
}

int Gauss1(double **A, int N)
{
    int i, j, k;
    double tmp;
    for(k = 0; k < N; k++)
        if ((i = find_not_zero(A, N, k)) != -1)
        {
            int M = 2*N;
            if (i != k)
            {
                swap_lines(A, k, i);
                printmatrix(A, N);
            }
            tmp = A[k][k];
            for(j = M - 1; j >= 0; j--)
                A[k][j] /= tmp;
            printmatrix(A, N);
            for(i = k + 1; i < N; i++)
            {
                double tmp = A[i][k];
                for(j = N + k + 1; j >= k; j--)
                    A[i][j] -= A[k][j]*tmp;
                printmatrix(A, N);
            }
        }
        else
            return 0;
    return 1;
}

void Gauss2(double **A, int N)
{
    int i, j, k;
    for(k = N - 1; k > 0; k--)
        for(i = k - 1; i >= 0; i--)
            for(j = 0; j < N; j++)
                A[i][N + j] -= A[k][N + j]*A[i][k]; //A[i][k] = 0;
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

void printmatrix(double **A, int N)
{
    int i, j;
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < 2*N; j++)
            printf("%lg ", A[i][j]);
        printf("\n");
    }
    printf("\n");
}
