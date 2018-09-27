#include <stdio.h>
#include <omp.h>
// Similar to before but utilizing static scheduling.
// This will have each thread do a minimum of 3 concurrent units of work (if possible) before moving on.

int main()
{
        int myid;
        int   i, n, chunk;
        int a[100], b[100], result;

        n = 52;
        result = 0;
        for (i=0; i < n; i++)
        {
                a[i] = i;
                b[i] = i * 2;
        }

        #pragma omp parallel reduction(+:result) private(myid) \
                        num_threads(10)
        {
        myid = omp_get_thread_num();
        printf("%2d reporting in...\n", myid);
        #pragma omp for  schedule(static, 3)
        for (i=0; i < n; i++)
        {
                printf("  %2d done by %2d\n", i, myid);
                //result = result + (a[i] * b[i]);
                result = myid;
        }
        }
        printf("Final result = %d\n",result);

        return 0;
}
