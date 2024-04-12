program
dana jest tablica intow (10)
wywoływany z linni polecen, w zaleznosci od wywołania:
PROG min    -znajdx minimalny
PROG sort   -posortuj
PROG sort desc  -posortuj malejaca
PROG inRange min max   true/false true/false -wypisz wszystki wartosci mieszczace sie w zakresie indeksów, true jesli min wchodzi do zakresu, false nie wchodzi do zakresiw,


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

enum bool {FALSE, TRUE};


void inRange(int tab[],int min, int max, enum bool minB, enum bool maxB)
{
    int start;
    int end;
    start=min;
    end=max;
    if(minB== FALSE)
    {
        start++;
    }
    if(maxB== TRUE)
    {
        end++;
    }
    for(int i=start;i<end;i++)
    {
        printf("%d ",tab[i]);
    }
}



int getMin(int tab[], int size) {
    int min = tab[0];
    for (int i = 1; i < size; i++) {
        if (tab[i] < min) {
            min = tab[i];
        }
    }
    return min;
}



void SortASC(int tab[],int n)
{
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (tab[j] > tab[j+1]) {
                // Zamiana miejscami
                temp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = temp;
            }
        }
    }
}




void SortDESC(int tab[],int n)
{
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (tab[j] < tab[j+1]) {
                // Zamiana miejscami
                temp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = temp;
            }
        }
    }
}



int main(int argc,char** argv)
{
    
    int tab[] = {10,9,8,7,6,5,4,3,2,1};
    if (argc ==2)
    {
        if (strcmp(argv[1], "min") == 0) {
            int min = getMin(tab, SIZE);
            printf("Minimalna wartość w tablicy: %d\n", min);
        } else if (strcmp(argv[1], "sort") == 0) {
            SortASC(tab, SIZE);
            printf("Tablica posortowana rosnąco:\n");
            for (int i = 0; i < SIZE; i++) {
                printf("%d ", tab[i]);
        }
            printf("\n");
        } else if (strcmp(argv[1], "sortDesc") == 0) 
        {
                SortDESC(tab, SIZE);
                printf("Tablica posortowana malejąco:\n");
                for (int i = 0; i < SIZE; i++) {
                    printf("%d ", tab[i]);
                }
                printf("\n");
        }
    }else if(argc == 6)
    {
        if (strcmp(argv[1], "inRange") == 0)
        {
            int min = atoi(argv[2]);
            int max = atoi(argv[3]);
            enum bool minB = strcmp(argv[4], "T") == FALSE;
            enum bool maxB = strcmp(argv[5], "T") == TRUE;
            inRange(tab, min, max, minB, maxB);
        }
    }else {printf("Zla ilosc argumentow");}
    
    return 0;
}