#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    //komputer
    srand(time(NULL));
    int t[3][4],k,v;
    while (k!=5)
    {
    k=0;
    for(int j=0;j<3;j++)
    {
        for(int i=0;i<4;i++)
        {
            v=rand();
            t[j][i]=v%2;
            if(v%2==1)
            {
                k++;
            }
            }
        }
    }
    //czlowiek
    int c[3][4],m,l;
    while (k!=5)
    {
    k=0;
    for(int j=0;j<3;j++)
    {
        for(int i=0;i<4;i++)
        {
            l=scanf("%d",c[j][i]);
            if(l%2==1)
            {
                m++;
            }
            }
        }
    }
    
    
    return 0;
}