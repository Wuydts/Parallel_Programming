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

                int rec;
                int isGiving = 1;
                MPI_Status returnStatus;

                while(isGiving)
                {
                        MPI_Recv(&rec, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &returnStatus);
                        printf("from part: %d data part: %d tag part: %d\n", returnStatus.MPI_SOURCE,rec, returnStatus.MPI_TAG);

                        if(returnStatus.MPI_TAG == 6)
                        {
                                isGivingData[returnStatus.MPI_SOURCE] = 0;
                        }

                        isGiving = 0;

                        for(int i = 0; i < worldSize; i++)
                        {
                                if(isGivingData[i] != 0)
                                isGiving = 1;
                        }
                }
        }

else
{
        int msg;
        int setup[] = {0,3,7,2,4,3};
        for(int i = 0; i < setup[myRank]; i++)
        {
                msg = myRank * 10;
                MPI_Send(&msg, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        }

        msg = 0;
        MPI_Send(&msg, 1, MPI_INT, 0, 6, MPI_COMM_WORLD);
}


MPI_Finalize();
return 0;
}
