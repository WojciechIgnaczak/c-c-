#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "function_types.h"

void printInRange(int * tab, struct argument * args, int size){
	int sizeTab;
  int min, max;
  bool minInclude, maxInclude;
	int i;
	
	sizeTab = atoi(args[0].value);
	
	min = atoi(args[1].value);
	max = atoi(args[2].value);
	minInclude = !strcmp(args[3].value,"T") ? true : false;
	maxInclude = !strcmp(args[4].value,"T") ? true : false;
	
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
