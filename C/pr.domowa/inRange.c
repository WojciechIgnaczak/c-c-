#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "min.h"
void printInRange(int * tab, struct argument *args,int size){
	int min,max;
	bool minInclude,maxInclude;
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

