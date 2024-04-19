#ifndef FUNCTION_TYPES
#define FUNCTION_TYPES

enum ArgType {INT, BOOL};

struct argument {
  char * name;
  enum ArgType type;
  char * value;
};

#endif
