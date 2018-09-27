#include <stdio.h>
#include <omp.h>
//Similar to reduce1.c but this one limits the amount of threads and tracks what is happening with each one.
int main()
{
        int   i, n, chunk;
        int a[100], b[100], result;

        n = 10;
        result = 0;
        for (i=0; i < n; i++)
        {
                a[i] = i;
                b[i] = i * 2;
        }

        #pragma omp parallel for  reduction(+:result) num_threads(4)
        for (i=0; i < n; i++)
        {
                result = result + (a[i] + b[i]);
                printf("%d done by %d --> %d\n", i, omp_get_thread_num(), result);
        }

        printf("Final result = %d\n",result);

        return 0;
}
