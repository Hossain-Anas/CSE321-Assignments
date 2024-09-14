#include <sys/types.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t a,b,c;

    int count = 0;

    a = fork();

    if(a == 0)
    {   
        count++;

        if(getpid() % 2 != 0)
        {
            fork();
            count++;
        }
    }

    b = fork();

    if(b == 0)
    {   
        count++;

        if(getpid() % 2 != 0)
        {
            fork();
            count++;
        }
    }

    c = fork();

    if(c == 0)
    {   
        count++;

        if(getpid() % 2 != 0)
        {
            fork();
            count++;
        }
    }



    printf("Number of Child Process : %d\n", count);


    return 0;
}