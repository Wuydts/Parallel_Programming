// pthread solution to Matrix Multiplication 
// Create 2 matricies at a predefined size, and then multiply them together. 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 5    // Size of Square Matrix
#define NUM_THREADS N

void fillMatrix(int n, int matrix[n][n]);
void displayMatrix(int n, int matrix[n][n]);
void sumMatrix(int n, int Amatrix[n][n], int Bmatrix[n][n], int Cmatrix[n][n], int t);

int A[N][N];
int B[N][N];
int C[N][N];    // matrix product, C = A x B

// 2. ENTRY POINT FOR THREADS
void *ThreadEntry( void* param)
{
    long t = (long) param;
    int i, j, k;
    int sum = 0;
	sumMatrix(N, A, B, C, t);

    // terminate thread when task is completed
    pthread_exit(NULL);
}

int main()
{
    // 1. DEFINE THREAD REF VARIABLES
    pthread_t tid[NUM_THREADS];

    void *status;
    long t;
    int i;

    // Fill matrices A & B with random #s
    fillMatrix(N, A);
    fillMatrix(N, B);

    printf("    A[%d][%d]\n", N, N);
    displayMatrix(N, A);

    printf("    B[%d][%d]\n", N, N);
    displayMatrix(N, B);

    // 3. CREATE THREADS
    for(t = 0; t < NUM_THREADS; t++ )
    {
        pthread_create( &tid[t], NULL, ThreadEntry, (void *) t );
    }

    printf("In main: all threads created\n");

    // 4. JOIN THREADS BACK UP
    for(i = 0; i < NUM_THREADS; i++)
    {
        pthread_join ( tid[i], &status);
    }
    printf("In main:  all threads joined\n");

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

void sumMatrix(int n, int A[n][n], int B[n][n], int C[n][n], int t)
{
     int i, j, k, sum=0;

    for(j = 0; j < N; j++)
    {
        for(k = 0; k < N; k++)
        {
            sum += A[t][k] * B[k][j];
        }

        C[t][j] = sum;
        sum = 0;
    }


}
