#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>

int ascii[3];
int idx = 0;
char name[3][50];
int arr_idx = 0;

int calculate(char name[])
{
    int count = 0;

    for(int i =0; name[i] != '\0'; i++)
    {
        count += name[i];
    }

    return count;
}

void *print_result(void* arg)
{
    if(ascii[0] == ascii[1] && ascii[1] == ascii[2])
    {
        printf("Youreka\n");
    }

    else if(ascii[0] == ascii[1] || ascii[1] == ascii[2] || ascii[0] == ascii[2])
    {
        printf("Miracle\n");
    }

    else
    {
        printf("Hasta la vista\n");
    }
}


void *block(void* arg)
{   

    printf("Enter User Name: \n");
    fgets(name[arr_idx], sizeof(name[arr_idx]), stdin);
    ascii[idx] = calculate(name[arr_idx]);
    idx++;
    arr_idx++;
}



int main()
{
    pthread_t thread[5];

    for(int i = 0; i<3; i++)
    { 
        pthread_create(&thread[i], NULL, block, NULL);
        sleep(1);
		pthread_join(thread[i], NULL);
    }

    pthread_t res;
    pthread_create(&res, NULL, print_result, NULL);
    pthread_join(res, NULL);


    return 0;

}