#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

int main()
{
    int x,y;
    scanf("%d %d", &x, &y);

    for(int i = x; i<=y; i++)
    {
        int sum = 0;

        for(int j = 1; j<i; j++)
        {
            if(i % j == 0) sum+=j;
        }

        if(sum == i) printf("%d\n", i);
    }

    return 0;
}