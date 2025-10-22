# Compiler and Flags
CC = gcc
CFLAGS = -Wall -g -Iinclude -MMD -MP

# Definition of src directory
SRC := $(wildcard src/*.c)
TESTS := $(wildcard tests/*.c)

# Objectfiles and target
OBJS := $(SRC:.c=.o) $(TESTS:.c=.o)
DEPS := $(OBJS:.o=.d)

# Define the target
TARGET := test

# Default target - build everything
all: $(TARGET)

# Link the object files
$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile all .c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Define the clean operation to remove all .o files
clean:
	rm -f src/*.o tests/*.o
	rm -f src/*.d tests/*.d

# Include automatically generated .d files (dependencies on headers)
-include $(DEPS)

# State that all and clean are no real files but commands (always execute)
.PHONY: all clean
