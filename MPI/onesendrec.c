
// first send and receive 

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int world_rank;
	int world_size;
	int number;

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
		number = 27;
		MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	else if (world_rank == 1)
	{
		MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process 1 received number %d from process 0\n", number);
	}

	MPI_Finalize();

}
