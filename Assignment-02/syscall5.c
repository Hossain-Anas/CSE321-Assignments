#include <sys/types.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

int main()
{
    pid_t cid, gid;

    cid = fork();

    // int count = 1;

    if(cid == 0)
    {
        printf("2. Child Process ID: %d\n", getpid());
        // count++;

        for(int i = 1; i<4; i++)
        {
            gid = fork();

            if(gid == 0)
            {
                printf("%d. Grand Child Process ID: %d\n", i+2, getpid());
                // count++;
                exit(0);
            }
        }
    

        for(int i = 0; i<3; i++)
        {
            wait(NULL);
        }

        exit(0);
    }

    else
    {
        printf("1. Parent Process ID: %d\n", getpid());
        // count++;

        wait(NULL);
    }
}