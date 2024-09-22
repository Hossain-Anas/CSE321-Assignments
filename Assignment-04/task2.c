#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
/*
This program provides a possible solution using mutex and semaphore.
use 5 Farmers and 5 ShopOwners to demonstrate the solution.
*/

#define MaxCrops 5 // Maximum crops a Farmer can produce or a Shpoowner can take
#define warehouseSize 5 // Size of the warehouse

sem_t empty;
sem_t full;

int in = 0;
int out = 0;

char crops[warehouseSize]={'R','W','P','S','M'}; //indicating room for different crops
char warehouse[warehouseSize]={'N','N','N','N','N'}; //initially all the room is empty

pthread_mutex_t mutex;


void *Farmer(void *far)
{
    /*
    1.Farmer harvest crops and put them in particular room. For example, room 0 for Rice(R).
    2.use mutex and semaphore for critical section.
    3.print which farmer is keeping which crops in which room inside the critical section.
    4.print the whole warehouse buffer outside of the critical section
    */

    int farmer_id = *(int *)far;

    for(int i = 0; i<MaxCrops; i++)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        warehouse[in] = crops[in];

        printf("Farmer %d: Insert crops %c at %d\n", farmer_id, warehouse[in], in);

        in = (in + 1) % warehouseSize;

        printf("Farmer%d: ", farmer_id);

        for(int i = 0; i < warehouseSize; i++)
        {
            printf("%c", warehouse[i]);
        }

        printf("\n");

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(0.5);
    }

}

void *ShopOwner(void *sho)
{
    /*
    1.Shop owner takes crops and makes that particular room empty.
    2.use mutex and semaphore for critical section.
    3.print which shop owner is taking which crops from which room inside the critical section.
    4.print the whole warehouse buffer outside of the critical section
    */

    int shopOwner_id = *(int *) sho;

    for(int i = 0; i<MaxCrops; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        printf("Shop owner %d: Remove crops %c from %d\n", shopOwner_id, warehouse[out], out);

        warehouse[out] = 'N';
        out = (out + 1) % warehouseSize;

        printf("ShopOwner%d: ", shopOwner_id);

        for(int i = 0; i<warehouseSize; i++)
        {
            printf("%c", warehouse[i]);
        }
        
        printf("\n");

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(1);

    }
}


int main()
{
    /*initializing thread,mutex,semaphore
    */
    pthread_t Far[5],Sho[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,warehouseSize);//when the warehouse is full thread will wait
    sem_init(&full,0,0);//when the warehouse is empty thread will wait
    int a[5] = {1,2,3,4,5}; //Just used for numbering the Farmer and ShopOwner
    /*create 5 thread for Farmer 5 thread for ShopOwner
    -------------------------------------------------
    -------------------------------------------------
    */


    for(int i = 0; i<5; i++)
    {
        pthread_create(&Far[i], NULL, Farmer, (void *)&a[i]);
        pthread_create(&Sho[i], NULL, ShopOwner, (void *)&a[i]);
    }

    for(int i = 0; i<5; i++)
    {
        pthread_join(Far[i], NULL);
        pthread_join(Sho[i], NULL);
    }


    // Closing or destroying mutex and semaphore
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;

}


//after following the instructions of the commented blocks-
//the output sequence doesn't match with the doc but it does the work
//the final line prints the empty Shop