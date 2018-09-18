
#include <stdio.h>
#include <omp.h>

int main()
{
        printf("Starting\n\n");

        //omp_set_num_threads ( 5 ); //-- This can be before the pragma in order to set it
        //                          -- However that will be for the whole program.


        #pragma omp parallel num_threads(3) // -- sets the num threads FOR THIS pragma as 3.
        {
                printf("Hello \n");
        }


        #pragma omp parallel num_threads(2) // -- sets the num threads FOR THIS pragma as 2.
        {
                printf("World \n");
        }


        printf("\n\nEnding \n");
        return 0;
}
