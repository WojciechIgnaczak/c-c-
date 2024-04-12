#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void printInRange(int * tab, int min, int max, bool minInclude, bool maxInclude){
        int i;

        if (!minInclude){
                min += 1;
        }

        if (!maxInclude){
                max -= 1;
        }

        for(i=min; i<=max; i++){
                printf("%d ", tab[i]);
        }
        printf("\n");
}

