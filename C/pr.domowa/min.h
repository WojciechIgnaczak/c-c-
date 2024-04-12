#ifndef TYPES
#define TYPES
enum ArgType{INT,BOOL};
struct argument{
char *name;
enum ArgType type;
char * value;
};

#endif
