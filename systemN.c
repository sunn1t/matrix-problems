#include <stdio.h>
#include <stdlib.h>

#define cor0(x) ((x) > -1e-10 && (x) < 1e-10 ? 0 : (x))

//Linear equations in n variables
//Gauss method

double** systemN_alloc(double N);
void systemN_free(double **A, int N);
int Gauss1(double **A, int N);
void Gauss2(double **A, int N);
int find_not_zero(double **A, int N, int column);
void swap_lines(double **A, int p, int r);

int main()
{
    int N, i, j;
    double **A = NULL;
    scanf("%d", &N);
    A = systemN_alloc(N);
    for(i = 0; i < N; i++)
        for(j = 0; j <= N; j++)
            scanf("%lf", &A[i][j]);
    if (Gauss1(A, N))
    {
        Gauss2(A, N);
        for(i = 0; i < N; i++)
            printf("%lg\n", cor0(A[i][N]));
    }
    else
        puts("NO");
    systemN_free(A, N);
    return 0;
}

double** systemN_alloc(double N)
{
    double **A = NULL;
    int i;
    A = (double**)malloc(N*sizeof(double*));
    for(i = 0; i < N; i++)
        A[i] = (double*)malloc((N + 1)*sizeof(double));
    return A;
}

void systemN_free(double **A, int N)
{
    int i;
    for (i = 0; i < N; i++)
        free(A[i]);
    free(A);
}

int Gauss1(double **A, int N)
{
    int i, j, k;
    for(k = 0; k < N; k++)
        if ((i = find_not_zero(A, N, k)) != -1)
        {
            if (i != k)
                swap_lines(A, i, k);
            for(j = N; j >= k; j--)
                A[k][j] /= A[k][k];
            for(i = k + 1; i < N; i++)
            {
                for(j = N; j >= k; j--)
                    A[i][j] -= A[k][j]*A[i][k];
            }
        }
        else
            return 0;
    return 1;
}

void Gauss2(double **A, int N)
{
    int i, k;
    for(k = N - 1; k > 0; k--)
        for(i = k - 1; i >= 0; i--)
        {
            A[i][N] -= A[k][N]*A[i][k];
            //Decreases value in the last column
            /*A[i][k] = 0; (-> 0 column above diagonal)*/
        }
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
