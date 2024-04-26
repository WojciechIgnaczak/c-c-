.PHONY: clean

DIR_OBJ := obj
DIR_SRC := src
DIR_BUILD := build

files_src := $(wildcard $(DIR_SRC)/*.c)

# Do NOT include spaces in the arguments after the first 'patsubst'.
# That will be seen as part of the string.
files_src := $(patsubst $(DIR_SRC)/%.c,%.c,$(files_src))
files_obj := $(patsubst %.c,%.o,$(files_src))
files_obj_full_path := $(patsubst %.o,$(DIR_OBJ)/%.o,$(files_obj))

all: $(DIR_BUILD)/main

# $@ - the target
# $^ - all prerequisites
# $? - all prerequisites newer than the target
# $< - only first prerequisite
$(DIR_BUILD)/main: $(files_obj_full_path)
	gcc $^ -o $@

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	gcc -c $< -o $@

clean:
	rm $(DIR_OBJ)/*.o



