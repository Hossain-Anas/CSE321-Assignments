#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>

int count = 1;


void *block(void* arg)
{
    int thread_serial = * ((int *) arg);

    for(int i = 0; i<5; i++)
    {
        printf("thread - %d prints %d\n", thread_serial, count);
        count++;
    }

    // printf("thread - %d running\n", thread_serial);
    sleep(1);
    // printf("thread - %d closed\n", thread_serial);
}



int main()
{
    pthread_t thread[5];

    for(int i = 0; i<5; i++)
    { 
        pthread_create(&thread[i], NULL, block, &i);
		pthread_join(thread[i], NULL);
		
    }
}