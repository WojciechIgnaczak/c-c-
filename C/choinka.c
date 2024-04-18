#include <stdio.h>

int main()
{   
    for(int j=0;j<=5;j++){
        for(int i=0;i<j;i++)
        {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}

