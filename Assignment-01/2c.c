#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char pass[100];

    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = '\0';

    int cap_flag = 0;
    int small_flag = 0;
    int num_flag = 0;
    int sp_flag = 0;

    for(int i = 0; i<strlen(pass); i++)
    {
        if(pass[i] >= 'A' && pass[i]<='Z')
        {
            cap_flag = 1;
        }

        else if (pass[i] >= 'a' && pass[i] <= 'z')
        {
            small_flag = 1;
        }

        else if(pass[i] >= '0' && pass[i] <= '0')
        {
            num_flag = 1;
        }

        else if(pass[i] == '@' || pass[i] == '#' || pass[i] == '$' 
        || pass[i] == '_' )
        {
            sp_flag = 1;
        }
    }


    if(cap_flag && small_flag && num_flag && sp_flag)
    {
        printf("OK\n");
    }

    if(!cap_flag) printf("Uppercase character missing, ");
    if(!small_flag) printf("Lowercase character missing, ");
    if(!sp_flag) printf("Special character missing, ");
    if(!num_flag) printf("Digit missing, ");

    printf("\n");

}