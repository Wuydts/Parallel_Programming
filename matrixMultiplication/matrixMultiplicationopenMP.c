// OpenMP solution to Matrix Multiplication 
// Create 2 matricies at a predefined size, and then multiply them together. 
// Do this utilizing openMP

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 5   // Size of Square Matrix

void fillMatrix(int n, int matrix[n][n]);
void displayMatrix(int n, int matrix[n][n]);
void sumMatrix(int n, int Amatrix[n][n], int Bmatrix[n][n], int Cmatrix[n][n]);
int main()
{
    int sum = 0;

    int A[N][N];
    int B[N][N];
    int C[N][N];    // matrix product, C = A x B

    // Fill matrices A & B with random #s
    fillMatrix(N, A);
    fillMatrix(N, B);

    printf("    A[%d][%d]\n", N, N);
    displayMatrix(N, A);

    printf("    B[%d][%d]\n", N, N);
    displayMatrix(N, B);
	
	sumMatrix(N, A, B, C);

    printf("    C[%d][%d]\n", N, N);
    displayMatrix(N, C);

    return 0;
}

void fillMatrix(int n, int matrix[n][n])
{
    int row, col;

    for(row = 0; row < n; row++)
    {
        for(col = 0; col < n; col++)
            matrix[row][col] = rand() % 10 + 1;   // random values in range 1 to 10
    }
}

void displayMatrix(int n, int matrix[n][n])
{
    int row, col;

    for(row = 0; row < n; row++)
    {
        for(col = 0; col < n; col++)
            printf("%5d", matrix[row][col]);

        printf("\n\n");
    }
}

void sumMatrix(int n, int A[n][n], int B[n][n], int C[n][n])
{
    int i = 0, j = 0, k = 0, sum = 0;

  #pragma omp parallel for firstprivate(sum)
    for( int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            for(int k = 0; k < N; k++)
            {
                sum += A[i][k] * B[k][j];
            }

            C[i][j] = sum;
            sum = 0;
        }
    }

}

