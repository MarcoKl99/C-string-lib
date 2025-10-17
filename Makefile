# Compiler and Flags
CC = gcc
CFLAGS = -Wall -g -Iinclude

# Definition of src directory
SRC = $(wildcard src/*.c)
TESTS := $(wildcard tests/*.c)

# Objectfiles and target
OBJS = $(SRC:.c=.o) $(TESTS:.c=.o)
TARGET = test

# Default target - build everything
all: $(TARGET)

# Link the object files
$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile main.c
main.o: main.c string_utils.h test_utils.h
	$(CC) $(CFLAGS) -c main.c

# Compile all .c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile main.c
tests/main.o: tests/main.c include/string_utils.h include/test_utils.h
	$(CC) $(CFLAGS) -c tests/main.c -o tests/main.o

clean:
	rm -f src/*.o tests/*.o
