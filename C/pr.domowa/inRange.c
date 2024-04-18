#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "min.h"
void printInRange(int * tab, struct argument *argc,int size){
	int min,max;
	bool minInclude,maxInclude;
        int i;
        min=atoi(argc[2].value);
        max=atoi(argc[3].value);
        minInclude= argc[4].value;
        maxInclude= argc[5].value;
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

