#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{

        int child_id;
        int dumb, val;

        printf("Start!\n");
        scanf("%d", &dumb);

        child_id = fork();
        if (child_id > 0)
        {
                printf("I'm the parent!\n");
                scanf("%d", &val);
                printf("P: %d\n", val);
                sleep(10);
        }
        else
        {
                printf("I'm the child!\n");
                scanf("%d", &val);
                printf("C: %d\n", val);
        }

        printf("End! Val was %d\n", val);
        scanf("%d", &dumb);




        return 0;
}
