
/*
Generate 10 random numbers and send


b) gen 10, then send 1 at a time


*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int world_rank;
	int world_size;
	int number;
	int k, x; // k is the loop. x is the generate number.
	int A[10];


	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // what rank am i
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);  // how many nodes are out there?

	// Must have 2 processes
	if (world_size != 2)
	{
		fprintf(stderr, "World size must be 2 for %s\n", argv[0]);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}


	if (world_rank == 0)
	{

		// If we are rank 0, set the number to 27 and send it to process 1
		x = 4;
		MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); // first message is a setup to let receive know how many are going to follow this one.

		for(k = 0; k < x; k++)
		{
			A[k] = rand() % 50 + 1;
		}

		for(k = 0; k < x; k++) // now  passing numbers one at a time from the array.
		{
			MPI_Send(&A[k], 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
			usleep(750000);
		}

	}

	else if (world_rank == 1)
	{
		MPI_Recv(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Remember that the first 0 is who it is coming from

		printf("%d \n", x);
		for(k = 0; k < x; k++)
		{
			MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Remember that the first 0 is who it is coming from
			printf("Process 1 received number %d from process 0\n", number);
		}
	}

MPI_Finalize();

}
