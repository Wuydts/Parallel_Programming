// pass the token around to each process
//  0 to 1 to 2 to 3 ... and back to 0

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
        // Initialize the MPI environment

        /*
        every single node is doing this exact same code... until mpi init happens.
        After MPI_Init then only the 1 process running it will see it.

        */

        MPI_Init(NULL, NULL);

        // Find out rank, size
        int my_rank;
        int world_size;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);


/////////////////////////////////////////////
        int token;

        if ( my_rank == 0 )
        {
                printf("Proc 0 of %d %d \n", my_rank, world_size);
                token = 42;

                MPI_Send(&token, 1, MPI_INT, (my_rank + 1) % world_size, 0, MPI_COMM_WORLD); // token variable, 1 intiger in size, the variable type, who I am sending it to,the tag, and comm world
                MPI_Recv(&token, 1, MPI_INT, world_size -1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                printf("Token at %d with value %d\n", 0, token);
        // Doesn't move ahead until it gets a message back.
        }

        else
        {       // sending variable and receiving variable don't have to be the same.
                MPI_Recv(&token, 1, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // variable, 1 intiger size, the type, and who it is coming from.
                                                //my_rank -1; if i am process 1 i get it from 0 and so on.

                printf("%d has token %d\n", my_rank, token);
                token++;

                MPI_Send(&token, 1, MPI_INT, (my_rank +1) % world_size, 0, MPI_COMM_WORLD); // token variable, 1 intiger in size, the ariable type, who I am sending it to,the tag, and comm world

        }

/////////////////////////////////////////////
        MPI_Finalize();
        return 0;
}
