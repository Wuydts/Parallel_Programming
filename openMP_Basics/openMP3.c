#include <stdio.h>
#include <unistd.h>
#include <omp.h>

/*
        Going to have 5 threads.
        if we just did omp parallel would mean every thread would do the for loop.
        By adding the for infront of the parallel it means that each one will do 2, and then 3 of them will do 3.
        We do the sleep to take a bit to see the work happening.

        When running the program notice how it does 5 at a time in parallel, sleeps, and then does it again.
*/

int main()
{
        int i = 0, tid, k, sum = 0;
        omp_set_num_threads (5);

//      #pragma omp parallel for private(tid)
        #pragma omp parallel for
        for (i = 0; i < 13; ++i)
        {
                sleep(1);
                tid = omp_get_thread_num();
                if(tid == 0)
                        sleep(2);
                printf("%2d by thread %2d\n", i, tid);

                sum += i;
        }
        printf("Sum is %d \n", sum);


        return 0;

}
