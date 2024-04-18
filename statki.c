/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
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
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", t[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //czlowiek
    int c[3][4],m=0,k=0,l;
    while (k!=5)
    {
    k=0;
    for(int j=0;j<3;j++)
    {
        for(int i=0;i<4;i++)
        {
            printf("Wprowadź wartość dla c[%d][%d]: ", j, i);
            l=scanf("%d",&c[j][i]);
            if(l%2==1)
            {
                k++;
            }
            }
        }
    }
    k++;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}