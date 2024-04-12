#include <stdio.h>

#include "types.h"
#include "functions.h"

void bar(struct ImportantStructure s){
printf("Function: bar\n");
helperFunction();
}

void helperFunction(){
printf("Function: helper\n");
}
