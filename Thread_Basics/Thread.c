#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM 8

int evenFunction(long);
int oddFunction(long);

void *threadFunction(void * param)
{
        long cValue = (long) param;
        long sum = 0;
        if (cValue % 2 == 0)
                sum = evenFunction(cValue);
        else
                sum = oddFunction(cValue);
        pthread_exit ( ( void*) sum);
}

int evenFunction(long cValue)
{
        int sum = 0;
        for (int j = 1; j <= cValue; j++)
        {
                sum  += j;
        }

//      printf("The summation of %d is %d \n", cValue, sum);

        return sum;

}

int oddFunction(long cValue)
{
        int sum = 1;
        for (int j = 1; j <= cValue; j++)
        {
                sum *= j;
        }

//      printf("The factorial of %d is %d \n", cValue, sum);

        return sum;
}





int main()
{
        pthread_t tid[NUM]; // An array of 8 elements of pthreads
        long i;
        void *returnValue;
        long total = 0;
        for(i = 1; i <= NUM; i++) // Creation of threads and passing them in.
        {
                pthread_create(&tid[i], NULL, threadFunction, (void *)i);
        }


        // join;
        for(int j = 1; j <= NUM; j++)
        {

        pthread_join(tid[j], &returnValue);

        printf("Hello, I am thread %d and ", j);
                if (j % 2 == 0)
                {
                        printf("I am even, my summation was %d \n", (long)returnValue);
                        total += (long)returnValue;
                }
                else
                {
                        printf("I am odd, my factorial was %d \n", (long)returnValue);
                        total += (long)returnValue;
                }
        }


        printf("The sum of all of them is: %d \n", total);

        return 0;
}
