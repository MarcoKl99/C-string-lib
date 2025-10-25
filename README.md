# C-string-lib - Implementation of utilities to work with Strings in C! 🚀

Welcome to this small project on a few implementations of utility functions regarding Strings in C!

## Goal 🎯

This project aims for deepening the understanding of concepts in C regarding Strings, represented as Arrays of Characters. When working with this data structure, simple implementations show the basics of concepts such as

- String initialization and representation
- Boundaries and the special null terminator `\0`
- Allocation on the Stack vs. Heap
- Usage of pointers (the classic topic... 😉) and memory management
- Basic structure of small projects
- Compilation process using Makefiles

Without using the string library `string.h`, this project implements basic functionalities as a learning path.

## Project Structure 🧭

The project is structured in the following way.

```text
C-string-lib/
├── include/
│ └── string_utils.h
├── src/
│ └── string_utils.c
├── tests/
│ └── main.c
└── Makefile
```

**include**: Header files

**src:** Actual implementation of the modules (.c files)

**tests:** Test programs

**Makefile:** Build instructions

## Functionalities ⚙️

- `str_equal`: Test if two given strings are equal
- `str_length`: Get the length of a given string
- `str_copy`: Copy a string from a source to a destination
- `str_concat`: Concatenate two strings and write the result into a buffer (and check against buffer overflow)
- `str_find`: Search for a substring (needle 🪡) in a string (haystack 🌾) and return the pointer to the first occurance... jup, that emoji was as close as I could get to a haystack

## How to build 🏗️

To build the project, execute the following.

```bash
make
make clean
./test
```

Have fun and happy coding! 🥳🎉
