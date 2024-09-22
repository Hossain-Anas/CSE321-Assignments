#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX 10 //producers and consumers can produce and consume upto MAX
#define BUFLEN 6
#define NUMTHREAD 2 /* number of threads */


void * consumer(int *id);
void * producer(int *id);

char buffer[BUFLEN];
char source[BUFLEN]; //from this array producer will store it's production into buffer


int pCount = 0;
int cCount = 0;
int buflen;


//initializing pthread mutex and condition variables
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;

int thread_id[NUMTHREAD] = {0,1};
int i = 0;
int j = 0;

int main()
{
    int i;
    /* define the type to be pthread */
    pthread_t thread[NUMTHREAD];
    strcpy(source,"abcdef");
    buflen = strlen(source);
    /* create 2 threads*/
    /* create one consumer and one producer */
    /* define the properties of multi threads for both threads */
    //Write Code Here

    pthread_create(&thread[0], NULL, (void *)producer, (void *)&thread_id[0]);
    pthread_create(&thread[1], NULL, (void *)consumer, (void *)&thread_id[1]);

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);


    pthread_mutex_destroy(&count_mutex);


}
void * producer(int *id)
{
    /*
    1. Producer stores the values in the buffer (Here copies values from source[] to buffer[]).
    2. Use mutex and thread communication (wait(), sleep() etc.) for the critical section.
    3. Print which produ4. Producer can produce up cer is storing which values using which thread
    inside the critical section.
    to MAX
    */
    //Write code here

    int producer_id = *(int *) id;

    while(pCount<MAX)
    {
        pthread_mutex_lock(&count_mutex);


        while(i == BUFLEN)
        {
            pthread_cond_wait(&full, &count_mutex);
        }

        int char_idx = pCount % BUFLEN;

        buffer[char_idx] = source[char_idx];

        printf("%d produced %c by Thread %d\n", pCount, buffer[char_idx], producer_id);

        pCount++;
        i++;

        pthread_cond_signal(&nonEmpty); //wasn't mentioned in our given doc
        pthread_mutex_unlock(&count_mutex);

        sleep(1);
    }
}


void * consumer(int *id)
{
    /*
    1. Consumer takes out the value from the buffer and makes it empty.
    2. Use mutex and thread communication (wait(), sleep() etc.) for critical section
    3. Print which consumer is taking which values using which thread inside the critical section.
    4. Consumer can consume up to MAX
    */
    //Write code here

    int consumer_id = *(int *) id;

    while(cCount < MAX)
    {
        pthread_mutex_lock(&count_mutex);

        while (i == 0)
        {
            pthread_cond_wait(&nonEmpty, &count_mutex);
        }

        int char_idx = cCount % BUFLEN;

        printf("%d consumed %c by Thread %d\n", cCount, buffer[char_idx], consumer_id);
        i--;
        cCount++;

        pthread_mutex_unlock(&count_mutex);

        sleep(2);
    }
}

//
//After following the instructions of the commented blocks in the given doc
//the output of this code doesn't exactly match with the given document, but it is theoretically correct. 
// Because thread 1 and thread 0 equally distribute the tasks and avoid deadlock.