#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void init_code()
// {
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// }

const int N = 1e5;

int checkPalindrome(char *str)
{
    char *l = str;
    char *r = strlen(str) - 1 + str;

    while(l < r)
    {
        if (*l != *r)
        {
            return 0;
        }

        l++;
        r--;
    }

    return 1;
}


int main()
{
    // init_code();
    char arr[N];

    fgets(arr, sizeof(arr), stdin);


    arr[strcspn(arr, "\n")] = '\0';

    // printf("%s\n", arr);

    if(checkPalindrome(arr))
    {
        printf("Palindrome\n");
    }
    else printf("Not Palindrome\n");

}

