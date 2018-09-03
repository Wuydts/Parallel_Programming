#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
        int child_id;
        int dumb, val;
        int pw, cw;
        int status;
        srand(time(NULL));
        pw = rand() % 7;
        cw = rand() % 7;

        printf("Start!\n");
        scanf("%d", &dumb);


        child_id = fork();
        if (child_id > 0)
        {
                printf("I'm the parent!, and I slept for %d\n", pw);
                sleep(pw);
                printf("Parent is now waiting! \n");
                wait(&status);
                printf("Parent is done waiting\n");

        }
        else
        {
                printf("I'm the child!, and I slept for %d\n", cw);
                sleep(cw + 10);
                printf("Child is leaving now \n");
                exit(2);

        }

        printf("End!\n");
        scanf("%d", &dumb);






        return 0;
}
