
#include <stdio.h>
#include <omp.h>

int main()
{

        int i = 0;
        int tid;
        printf("Starting\n\n");

        //omp_set_num_threads ( 5 ); //-- This can be before the pragma in order to set it
        //                          -- However that will be for the whole program.


        #pragma omp parallel num_threads(3) private(tid) // -- sets the num threads FOR THIS pragma as 3.
        {
                tid = omp_get_thread_num();
                i++; // i essentially beomes a shared variable. But if you add some sleeps you will quickly
                        // find that it can break a bunch of things.
                //sleep(1);
                printf("%d says Hello %d\n",tid,  i);
        }


        #pragma omp parallel num_threads(2) // -- sets the num threads FOR THIS pragma as 2.
        {
                printf("World \n");
        }


        printf("\n\nEnding \n");
        return 0;
}

