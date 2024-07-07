#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char arr[100];

    fgets(arr, sizeof(arr), stdin);
    arr[strcspn(arr, "\n")] = '\0';

    char original_domain[] = "sheba.xyz";
    char check[50];

    char *substr = strchr(arr, '@');

    substr++;

    strcpy(check, substr);

    // printf("%s\n", substr);
    // printf("%s\n", check);

    int flag = 0;

    for(int i = 0; i<=strlen(original_domain); i++)
    {
        if(original_domain[i] == '\0' ^ check[i] == '\0')
        {
            flag = 1;
            break;
        }

        else if(original_domain[i] != check[i])
        {
            flag = 1;
            break;
        }
    }

    if(flag) printf("Email address is outdated\n");
    else printf("Email address is okay\n");


}