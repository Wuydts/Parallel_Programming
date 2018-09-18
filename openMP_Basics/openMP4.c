#include <stdio.h>
#include <omp.h>
/*
        Broken into 3 segments because of the barriers.

        prints out 5 times.
        gets the alone 1 time.
        prints out 5 times.
*/

int main()
{
        int i = 0, me;
        omp_set_num_threads(5);

        #pragma omp parallel private(me)
        {
                me = omp_get_thread_num();
                printf("Hello, from %d\n", me);

                #pragma omp barrier

                #pragma omp single
                        printf("I'm Alone, %d \n", me);

                #pragma omp barrier

                printf("Bye, from %d\n", me);
        }


        return 0;
}
