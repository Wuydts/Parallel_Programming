#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
        // Initialize the MPI environment
        MPI_Init(NULL, NULL);

        // Find out rank, size
        int myrank;
        int world_size;

        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        /////////////////////////////////////////////

        int list_size = 16;
        int recv_size = list_size / world_size;

        int recv[recv_size];

        int arr[list_size];

//Proc 0:  generate & fill int [16]
//Share a portion of the list with each of the 4 nodes
        if (myrank == 0)
        {
                for (int i = 0; i < list_size; i++) {
                        arr[i] = 15 - i;
                }
        }

        MPI_Scatter(arr, recv_size, MPI_INT, recv, recv_size, MPI_INT, 0, MPI_COMM_WORLD);

//Everyone find the sum of their part of the list
        int partial_sum = 0;
        for (int i = 0; i < recv_size; i++)
        {
                partial_sum += recv[i];
        }

        int red;
        MPI_Reduce(&partial_sum, &red, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

        if(myrank == 0)
        {
                printf("Total sum: %d\n", red);
        }




        /////////////////////////////////////////////
        MPI_Finalize();
        return 0;
}

