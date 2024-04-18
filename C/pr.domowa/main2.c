
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "min.h"
#include "min2.h"
#include "inRange.h"


int main(int argc, char ** argv) {
                   //0  1  2  3  4  5  6
        int tab[] = {5, 1, 2, 7, 3, 4, 6};
        char bufferMain[32];
        int len;
        if (argc == 1) {
                printf("Bad program call\n");
        } else if (argc == 2) {
                if (!strcmp(argv[1], "min")){
                        struct argument args[1];
                        char * buffer;

                        args[0].type=INT;
                        args[0].name="size";
                        sprintf(bufferMain,"%d",7);
                        len= strlen(bufferMain);
                        buffer= malloc(sizeof(int)*(len+1));
                        strcpy(buffer,bufferMain);
                        args[0].value=buffer;
                       printMin(tab,args,1);
                        free(args[0].value);
			//free(args[0].name);
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
                                return 1;
                        }

                        if (!strcmp(argv[5], "T")) {
                                maxInclude = true;
                        } else if (!strcmp(argv[5], "F")) {
                                maxInclude = false;
                        } else {
                                printf("Bad program call\n");
                                return 1;
                        }

                        printInRange(tab,argc, 1);
                }
        }
        return 0;
}


