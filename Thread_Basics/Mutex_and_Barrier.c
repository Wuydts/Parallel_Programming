#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int globX; // Our Shared global variables
pthread_mutex_t lock;
pthread_barrier_t barr;


void *sayhi( void *param)
{
        int myid;
        int j;
        myid  =  (long) param ;
        int tmp;

        printf("  aa     -- hi from %d \n", myid);

pthread_barrier_wait ( &barr );
        j = rand() % 4;
        sleep(j);

pthread_mutex_lock( &lock );
        tmp = globX;
        tmp = tmp + 1;
        globX = tmp;
        printf("       -- hi from %d  see global %d\n", myid, globX);
pthread_mutex_unlock ( &lock );

pthread_barrier_wait ( &barr );

        printf("  bb     -- hi from %d \n", myid);
        pthread_exit(NULL);
}

int main()
{
        pthread_t tid[5];
        void *status;
        int i;

        srand(time(NULL));
        globX = 25;

pthread_mutex_init ( &lock, NULL);
pthread_barrier_init ( &barr, NULL, 5);

        printf("In main: time to build threads\n");
        printf("Global1:  %d\n", globX);
        for ( i = 0; i < 5; ++i)
        {
                printf("   In main: creating thread %d\n", i);
                pthread_create( &tid[i], NULL, sayhi, (void *)(long) i );
        }
        printf("In main: all threads created\n");

        for ( i = 0; i < 5; ++i)
        {
                pthread_join( tid[i], &status );
                printf("   Main: joined %d\n", i);
        }

        printf("In main:  all threads joined\n");
        printf("Globall:  %d\n", globX);

        return 0;
}
