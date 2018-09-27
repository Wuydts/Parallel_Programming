#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
        int i,k;
        int tid;
        int x,y;
        i = 0;

        omp_set_num_threads(5);

                #pragma omp parallel sections private(tid)
                {
                printf("hi\n");
                #pragma omp section
                        {
                tid = omp_get_thread_num(); // Sets x variable
                                printf("Section 1: %d\n", tid);
                                x = 20 + tid;
                        }
                #pragma omp section
                        {
                tid = omp_get_thread_num();
                                printf("Section 2: %d\n", tid);
                                y = 50 + tid; // Sets Y variable
                        }

                } // Parallel region ends and we can see which thread did what. Even if we have more threads then needed we can see that the rest just skip ahead and wait.

        printf("Done X: %d  Y: %d\n", x, y);

        return 0;
}
