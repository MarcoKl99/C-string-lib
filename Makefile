# Compiler and Flags
CC = gcc
CFLAGS = -Wall -g -Iinclude

# Definition of src directory
SRC = $(wildcard src/*.c)

# Objectfiles and target
OBJS = $(SRC:.c=.o)
TARGET = test_strings

# Default target - build everything
all: $(TARGET)

# Link the object files
$(TARGET) : $(OBJS) tests/main.o
	$(CC) $(OBJS) tests/main.o -o $(TARGET)

# Compile main.c
main.o: main.c string_utils.h
	$(CC) $(CFLAGS) -c main.c

# Compile all .c files in src
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile main.c
tests/main.o: tests/main.c include/string_utils.h
	$(CC) $(CFLAGS) -c tests/main.c -o tests/main.o

clean:
	rm -f src/*.o tests/*.o
