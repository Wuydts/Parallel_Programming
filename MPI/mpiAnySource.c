#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main()
{
        MPI_Init(NULL,NULL);

        int myRank;
        int worldSize;

        MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
        MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

        int isGivingData[worldSize];

        if(myRank == 0)
        {
                for(int i = 0; i < worldSize; i++)
                {
                        isGivingData[i] = i;
                }

                int rec[3];
                int isGiving = 1;

                while(isGiving)
                {
                        MPI_Recv(rec, 3, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        printf("first part: %d second part: %d third part: %d\n", rec[0], rec[1], rec[2]);
                        if(rec[2] == 6)
                        {
                                isGivingData[rec[0]] = 0;
                        }

                        isGiving = 0;

                        for(int i = 0; i < worldSize; i++)
                        {
                                if(isGivingData[i] != 0)
                                {
                                        isGiving = 1;
                                }
                        }
                }
        }

        else
        {
                int msg[3];
                int setup[] = {0,3,7,2,4,3};
                msg[0] = myRank;
                msg[2] = 2;

                for(int i = 0; i < setup[myRank]; i++)
                {
                        msg[1] = myRank * 10;
                        MPI_Send(msg, 3, MPI_INT, 0, 0, MPI_COMM_WORLD);
                }

                msg[2] = 6;
                MPI_Send(msg, 3, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }



        MPI_Finalize();
        return 0;
}
