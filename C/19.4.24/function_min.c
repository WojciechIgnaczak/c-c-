#include <stdio.h>
#include <stdlib.h>

#include "function_types.h"

void printMin(int * tab, struct argument * args, int size){
	int i;
  int sizeTab;
	int min;

  sizeTab = atoi(args[0].value);
  
  min = tab[0];
  
	for(i=1; i<sizeTab; i++){
		if (tab[i]<min){
			min = tab[i];
		}
	}
  
	printf("min=%d\n", min);
}

