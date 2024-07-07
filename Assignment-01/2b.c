#include <stdio.h>
#include <stdlib.h>

void init_code() 
{
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
}

int main()
{
    init_code();

    const int N = 1e5;
    char arr[N];

    char new_arr[N];

    fgets(arr, sizeof(arr), stdin);
    

    int i = 0, j = 0;

    while(arr[i] != '\0')
    {
        if(arr[i] != ' ')
        {   
            new_arr[j] = arr[i];
            i++;
            j++;
        }

        else if(arr[i] == ' ' && arr[i+1] != '\0' && arr[i+1] != ' ')
        {
            new_arr[j] = arr[i];
            i++;
            j++;
        }

        else if(arr[i] == ' ' && arr[i+1] != '\0' && arr[i+1] == ' ')
        {
            i++;
        }
    }

    new_arr[j] = '\0';

    
    // int a = 0;

    // while(arr[a] != '\0')
    // {
    //     printf("%c", arr[a]);
    //     a++;
    // }
    // printf("\n");
    printf("%s\n", new_arr);

}