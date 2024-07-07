#include <stdio.h>

// void init_code() 
// {
//     #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
//     #endif
// }

int main()
{
    // init_code();

    int x,y;
    scanf("%d %d", &x, &y);

    if(x>y)
        printf("%d\n", x-y);
    
    else if(x<y)
        printf("%d\n", x+y);
    else
        printf("%d\n", x*y);
    
    return 0;

}