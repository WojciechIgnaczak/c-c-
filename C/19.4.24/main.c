#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "function_types.h"
#include "function_min.h"
#include "function_inrange.h"

int main(int argc, char ** argv) {
	           //0  1  2  3  4  5  6
	int tab[] = {5, 1, 2, 7, 3, 4, 6};
  int len;
	char bufferMain[32];

	if (argc == 1) {
		printf("Bad program call\n");
	} else if (argc == 2) {
		if (!strcmp(argv[1], "min")){
      struct argument args[1];
      char * buffer;



      args[0].type = INT;
      args[0].name = "size";

      sprintf(bufferMain, "%d", 7);
      len = strlen(bufferMain);
      buffer = malloc(sizeof(int)*(len+1));
      strcpy(buffer, bufferMain);
      args[0].value = buffer;   
      
      args[0]=arguments_constructor("size",INT,dataStr); //nazwa, rodzaj, powinna zwracac wskaznik na obiekt

      printMin(tab, args, 1);
      //printMin(tab, 7);
      free(args[0].value);
		}
	} else if (argc == 6) {
		if (!strcmp(argv[1], "inRange")){
			bool minInclude, maxInclude;
			int min, max;

			if (strcmp(argv[4], "T") && strcmp(argv[4], "F")) {
				printf("Bad program call\n");
				return EXIT_FAILURE;
			}
				
			if (strcmp(argv[5], "T") && strcmp(argv[5], "F")) {
				printf("Bad program call\n");
				return EXIT_FAILURE;
			}
			
			struct argument args[5];
                        char * buffer;
						
			// inRange min			
                        args[1].type = INT;
                        args[1].name = "min";

                        len = strlen(argv[2]);
                        buffer = malloc(sizeof(int)*(len+1));
                        strcpy(buffer, argv[2]);
                        args[1].value = buffer;
			
			// inRange max
			args[2].type = INT;
                        args[2].name = "max";

                        len = strlen(argv[3]);
                        buffer = malloc(sizeof(int)*(len+1));
                        strcpy(buffer, argv[3]);
                        args[2].value = buffer;
			
			// inRange minInclude
			args[3].type = BOOL;
                        args[3].name = "min";

                        len = strlen(argv[4]);
                        buffer = malloc(sizeof(int)*(len+1));
                        strcpy(buffer, argv[4]);
                        args[3].value = buffer;
			
			// inRange maxInclude
			args[4].type = BOOL;
                        args[4].name = "max";

                        len = strlen(argv[5]);
                        buffer = malloc(sizeof(int)*(len+1));
                        strcpy(buffer, argv[5]);
                        args[4].value = buffer;
			
			// data tab size
			args[0].type = INT;
                        args[0].name = "size";

                        sprintf(bufferMain, "%d", 7);
                        len = strlen(bufferMain);
                        buffer = malloc(sizeof(int)*(len+1));
                        strcpy(buffer, bufferMain);
                        args[0].value = buffer;
      
		        printInRange(tab, args, 5);
			//printInRange(tab, min, max, minInclude, maxInclude);
			
			free(args[0].value); //argument_desctructor(args[0]);
			free(args[1].value);
			free(args[2].value);
			free(args[3].value);
			free(args[4].value);
		}
	}
	return EXIT_SUCCESS;
}

