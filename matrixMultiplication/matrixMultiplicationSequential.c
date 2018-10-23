// Sequential solution to Matrix Multiplication 
// Create 2 matricies at a predefined size, and then multiply them together. 

#include <stdio.h>
#include <stdlib.h>

#define N 5   // Size of Square Matrix

void fillMatrix(int n, int matrix[n][n]);
void displayMatrix(int n, int matrix[n][n]);
void sumMatrix(int n, int Amatrix[n][n], int Bmatrix[n][n], int Cmatrix[n][n]);
int main()
{

    int A[N][N];
    int B[N][N];
    int C[N][N];    // matrix product, C = A x B

    // Fill matrices A & B with random #s
    fillMatrix(N, A); // size, matrix
    fillMatrix(N, B); // size, matrix

    printf("    A[%d][%d]\n", N, N); // Print display to say what size of matrix is, and which matrix it is.
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
		{
            matrix[row][col] = rand() % 10 + 1;   // random value in range 1 to 10
		}	
    }
}

void displayMatrix(int n, int matrix[n][n])
{
    int row, col;

    for(row = 0; row < n; row++)
    {
        for(col = 0; col < n; col++)
		{
            printf("%5d ", matrix[row][col]); 
		}	

        printf("\n\n");
    }
}

void sumMatrix(int n, int A[n][n], int B[n][n], int C[n][n])
{
    int i = 0, j = 0, k = 0, sum = 0;

  for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            for(k = 0; k < N; k++)
			{
                sum += A[i][k] * B[k][j];
			}	

            C[i][j] = sum;
            sum = 0;
        }
    }


}

 
