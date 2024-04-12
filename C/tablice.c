#include <stdio.h>

int main()
{
    int i,x;
    int t[5];
    int g[3]={100,101,102};
    int k[]={200,201,202,203,204};
    for(i=0;i<5;i++)
    {
        scanf("%d",&x);
        t[i]=x;
        /*printf("%d\n",t[i]);/* %d- liczba calkowita*/
    }
    for(int j=0;j<5;j++)
    {
        printf("%d\n",t[j]);
    }
    return 0;
}

#include <stdio.h>

int main()
{
    int m[3][2];
    int n[3][2]={{1,2},{3,4},{5,6}};
    int k[][2]={{1,2},{3,4},{5,6}};
    int l[3][2]={1,2,3,4,5,6};
    printf("%d",n[1][2]);
    return 0;
}


#include <stdio.h>

int main()
{
    int t[3][4];
    for(int j=0;j<=3;j++)
    {
        for(int i=0;i<=2;i++)
        {
            if((i+j)%2==0)
            {
                t[i][j]=0;
            }
            else
            {
                t[i][j]=1;
            }
        }
    }
    
    
    
    for(int p=0;p<3;p++)
    {
        for(int k=0;k<4;k++){
        printf("%d",t[p][k]);
        }
        printf("\n");
    }

    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    srand(time(NULL));

    int t[3][4];
    for(int j=0;j<3;j++)
    {
        for(int i=0;i<4;i++)
        {
            int v=rand();
            if((v)%2==0)
            {
                t[i][j]=0;
            }
            else
            {
                t[i][j]=1;
            }
        }
    }
    
    
    for(int p=0;p<3;p++)
    {
        for(int k=0;k<4;k++){
        printf("%d",t[p][k]);
        }
        printf("\n");
    }

    return 0;
}




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
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
                /*printf("%d\n",k);*/
            }
        }
    }
    
    
    
    for(int p=0;p<3;p++)
    {
        for(int l=0;l<4;l++){
        printf("%d",t[p][l]);
        }
        printf("\n");
    }

    return 0;
}
