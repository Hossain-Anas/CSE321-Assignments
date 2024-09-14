#include <sys/types.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

const int N = 10e3;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low-1;

    for(int j=low; j<=high-1; j++)
    {
        if(arr[j]<=pivot)
        {
            i++;
            swap(&arr[j], &arr[i]);
        }
    }
    i++;
    swap(&arr[high], &arr[i]);
    return i;
}


void quicksort(int arr[], int low, int high)
{
    if (low<high)
    {
        int pivot = partition(arr, low, high);
        quicksort(arr, low, pivot-1);
        quicksort(arr, pivot+1, high);
    }
}

int main(int argc, char* argv [])
{
    
    int arr[N];

    int j = 0;

    for(int i = 1; i<argc; i++)
    {
        arr[j] = atoi(argv[i]);
        j++;
    }

    pid_t pid = fork();

    if(pid == 0)
    {
        quicksort(arr, 0, j-1);

        printf("Sorted Array : ");

        for(int i = j-1; i > -1; i--)
        {
            printf("%d ", arr[i]);
        }

        printf("\n");
        
    }

    if(pid > 0)
    {
        wait(NULL);

        for(int i = 0; i<j; i++)
        {
            if(arr[i] % 2 == 0 ) printf("%d is Even\n", arr[i]);
            else printf("%d is Odd\n", arr[i]);
        }
    }

    printf("\n");

    
    return 0;
}
