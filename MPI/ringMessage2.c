// pass the token around, utilizing an array, to each process
//  0 to 1 to 2 to 3 ... and back to 0

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
        // Initialize the MPI environment


        MPI_Init(NULL, NULL);

        // Find out rank, size
        int my_rank;
        int world_size;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);


/////////////////////////////////////////////
        int token[2]; // token is now an array of 2 integers

        if ( my_rank == 0 )
        {
                printf("Proc 0 of %d %d \n", my_rank, world_size);
                token[0] = 42;  // [0] is the message
                token[1] = world_size -2;  //  [1] is the node we want.

                // changed the int to a 2 because our array is 2 ints in size.
                MPI_Send(&token, 2, MPI_INT, (my_rank + 1) % world_size, 0, MPI_COMM_WORLD);

                MPI_Recv(&token, 2, MPI_INT, world_size -1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                printf("Token at %d with value %d\n", 0, token[0]);
        }
        else
        {
                MPI_Recv(&token, 2, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                if(token[1] == my_rank)
                {
                        printf("Got it -- %d has token %d\n", my_rank, token[0]);
                        token[1] = -1;
                }


                MPI_Send(&token, 2, MPI_INT, (my_rank +1) % world_size, 0, MPI_COMM_WORLD);

        }

/////////////////////////////////////////////
        MPI_Finalize();
        return 0;
}
