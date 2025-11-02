# Compiler and Flags
CC = gcc
CFLAGS = -Wall -g -Iinclude -MMD -MP

# Definition of src directory
SRC := $(wildcard src/*.c)
TESTS := $(wildcard tests/*.c)
CLI := $(wildcard cli/*.c)

# Objectfiles
OBJS_TEST := $(SRC:.c=.o) $(TESTS:.c=.o)
OBJS_CLI := $(SRC:.c=.o) $(CLI:.c=.o)
DEPS := $(OBJS_TEST:.o=.d) $(OBJS_CLI:.o=.d)

# Define the targets
TARGET_TEST := test
TARGET_CLI := templater

# Default target - build everything
all: $(TARGET_TEST) $(TARGET_CLI)

# Build the test binary
$(TARGET_TEST) : $(OBJS_TEST)
	$(CC) $(OBJS_TEST) -o $(TARGET_TEST)

# Build the cli binary
$(TARGET_CLI) : $(OBJS_CLI)
	$(CC) $(OBJS_CLI) -o $(TARGET_CLI)

# Compile all .c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Define the clean operation to remove all .o files
clean:
	rm -f src/*.o tests/*.o cli/*.o
	rm -f src/*.d tests/*.d cli/*.d

# Include automatically generated .d files (dependencies on headers)
-include $(DEPS)

# State that all and clean are no real files but commands (always execute)
.PHONY: all clean
