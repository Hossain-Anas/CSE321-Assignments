#include <sys/types.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

const int N = 10e3;



int main(int argc, char* argv [])
{
    
    int arr[N];

    int j = 0;

    for(int i = 1; i<argc; i++)
    {
        arr[j] = atoi(argv[i]);

        if(arr[j] % 2 == 0 )
        {
            printf("Even\n");
        }
        
        else printf("Odd\n");
        j++;
    }

    return 0;

}