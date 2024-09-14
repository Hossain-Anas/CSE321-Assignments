#include <stdio.h>
#include <strings.h>
#include <stdlib.h>


int main(int argc, char* argv [])
{
    freopen(argv[1], "w", stdout);

    char txt_input[1010];

    while (1)
    {
        fgets(txt_input, sizeof(txt_input), stdin);

        if (txt_input[strlen(txt_input) - 1] == '\n') 
        {
            txt_input[strlen(txt_input) - 1] = '\0';
        }

        if (strcmp(txt_input, "-1") == 0) 
        {
            break;
        }

        printf("%s\n", txt_input);
    }

    fclose(stdout);

    return 0;
}

