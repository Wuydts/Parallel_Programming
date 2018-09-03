#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
        int child_id;
        int dumb, val;
        int pw, cw;
        srand(time(NULL));
        pw = rand() % 7;
        cw = rand() % 3;

        printf("Start!\n");
        scanf("%d", &dumb);

        cw = 5;
        pw = 10;

        child_id = fork();
        if (child_id > 0)
        {
                sleep(pw);
                printf("I'm the parent!, and I slept for %d\n", pw);

        }
        else
        {
                sleep(cw);
                printf("I'm the child!, and I slept for %d\n", cw);
                printf("Child is leaving now \n");
                exit(2);

        }

        printf("End! %d \n", val);
        scanf("%d", &dumb);






        return 0;
}
