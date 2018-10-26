/*
Generate 10 random numbers and send
a) gen 1 value, send immediately
  -- we'll put a short sleep in each program
	  to make the behavior more obvious

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



	x = 999;
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
		for(k = 0; k< 10; k++)
	{
		number = rand() % 50 + 1;
		MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		usleep(750000);
	}


	}
	
	else if (world_rank == 1)
	{
		printf("%d \n", x);
		for(k = 0; k< 10; k++)
	{
		MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process 1 received number %d from process 0\n", number);
	}


	}

MPI_Finalize();

}
