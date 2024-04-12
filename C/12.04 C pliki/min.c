#include <stdio.h>
void printMin(int * tab, int size){
        int i;
        int min = tab[0];

        for(i=1; i<size; i++){
                if (tab[i]<min){
                        min = tab[i];
                }
        }

        printf("min=%d\n", min);
}
