#include <sys/types.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid, pid2;

    pid = fork();

    if(pid > 0)
    {
        printf("I am parent\n");
        wait(NULL);
    }

    else if(pid == 0)
    {
        pid2 = fork();

        if(pid2 > 0)
        {
            printf("I am child\n");
            wait(NULL);
            
        }

        if(pid2 == 0)
        {
            printf("I am grandchild\n");
        }
    }
    return 0;
}