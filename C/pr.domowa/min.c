#include <stdio.h>
#include <stdlib.h>
#include "min.h"//  to ich types.h
//strutura name, value,
void printMin(int * tab,struct argument * args, int size){
        int i,sizeTab;
        int min;
	min = tab[0];
	sizeTab=atoi(args[0].value);
	printf("%s, %d\n",args[0].name,sizeTab);

        for(i=1; i<sizeTab; i++){
                if (tab[i]<min){
                        min = tab[i];
                }
        }

        printf("min=%d\n", min);
}
