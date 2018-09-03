#include <stdio.h>
#include <unistd.h>

int main(int argc, char **arv)
{
        printf("--beginning of program\n");

        int counter = 0;

        pid_t pid = fork();

        if(pid == 0)
        {
                //child process
                for(int i = 0; i < 5; ++i)
                {
                        sleep(1);
                        printf("Child Process: Counter = %d \n", ++counter);
                }
        }
        else if (pid > 0)
        {
                //Parent Process
                for(int j = 0; j < 5; ++j)
                {
                        sleep(1);
                        printf("Parent Process: Counter = %d\n", ++counter);

                }

        }
        else
        {
                //Fork Failed
                printf("fork() failed! \n");
                return 1;
        }

        printf("== End of Program == \n");

        return 0;
}
