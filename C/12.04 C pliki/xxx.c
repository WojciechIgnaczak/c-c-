#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void printMin(int * tab, int size);
void printInRange(int * tab, int min, int max, bool minInclude, bool maxInclude);

int main(int argc, char ** argv) {
	           //0  1  2  3  4  5  6
	int tab[] = {5, 1, 2, 7, 3, 4, 6};
	
	if (argc == 1) {
		printf("Bad program call\n");
	} else if (argc == 2) {
		if (!strcmp(argv[1], "min")){
			printMin(tab, 7);
		}
	} else if (argc == 6) {
		if (!strcmp(argv[1], "inRange")){
			bool minInclude, maxInclude;
			int min, max;

			if (!strcmp(argv[4], "T")) {
				minInclude = true;
			} else if (!strcmp(argv[4], "F")) {
				minInclude = false;
			} else {
				printf("Bad program call\n");
				return EXIT_FAILURE;
			}
				
			if (!strcmp(argv[5], "T")) {
				maxInclude = true;
			} else if (!strcmp(argv[5], "F")) {
				maxInclude = false;
			} else {
				printf("Bad program call\n");
				return EXIT_FAILURE;
			}
			
			min = atoi(argv[2]);
			max = atoi(argv[3]);	
			
			printInRange(tab, min, max, minInclude, maxInclude);
		}
	}
	return EXIT_SUCCESS;
}

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
