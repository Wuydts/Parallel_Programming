/*Shared variable that both processes can see */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
        int *glob_var;
        glob_var = mmap(NULL, sizeof *glob_var, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

        *glob_var = 1;

        printf("Before fork: %d\n", *glob_var);

        if(fork() == 0)
        {
                sleep(3);
                *glob_var = 5;
                printf("Child %d\n", *glob_var);
                exit(EXIT_SUCCESS);
        }
        else
        {
                sleep(2);
                printf("Parent %d\n", *glob_var);
                wait(NULL);
                printf("Parent after wait %d\n", *glob_var);
                munmap(glob_var, sizeof *glob_var); //GIves Memory back to the system

        }
//      printf("At End: %d\n", *glob_var);

        return 0;
}
