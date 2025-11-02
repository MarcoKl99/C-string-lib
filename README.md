# C-string-lib - Implementation of utilities to work with Strings in C! 🚀

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

Welcome to this small project on a few implementations of utilites regarding Strings in C!

This project implements simple helper functions on char * like `str_equal` or `str_length`, I extended these functions to many cases, tested it and was happy with the outcome... when suddenly... 😮

I was driving home from work 🚎, thinking about the next utility that I could implement... when a capable LLM decided to teach me about the concept of *memory ownership*!

When performing operations on char * instances, suddenly a wild memory leak occured! To neutralize the threat, our heros (me and ChatGPT) started to implement a struct, wrapping the string's content (as a `char *`) into their own data structure and therfore passing the responsibility of memory management from the caller to the cellee. After properly free-ing the memory and NULL-ing remaining pointers to that memory, the villagers could finally sleep well again... as far as this project goes, I know there are still fragments of the code that allow for that, but the basic concept is implemented in the usage of *dstruct_t*, don't be too strict plz 😉.

In summary, this project provides a struct *dstring_t* that stores a pointer to a data array as well as the length of the string and the current capacity.

```c
typedef struct
{
    char *data;
    size_t length;
    size_t capacity;
} dtype_d;
```

This dynamic string struct enables the caller to simply continue working with the current object, the reallocation of capacity is wrapped inside of the utility functions and abstracted away from the user, avoiding certain cases of memory leaks in the code.

Also, the logic follows the principle of exponential growth of capacity when extending beyond, which results in an armortized complexity of O(1) per append.

## Goal 🎯

While certainly not winning an award 🏆, this project aims for deepening the understanding of concepts in C regarding Strings, represented as Arrays of Characters, toghether with structs, memory ownership, memory leaks, dangling pointers and many more! When working with this data structure, simple implementations show the basics of concepts such as

- String initialization and representation
- Boundaries and the special null terminator `\0`
- Allocation on the Stack vs. Heap
- Usage of pointers (the classic topic... 😉) and memory management
- Basic structure of small projects
- Compilation process using Makefiles

Without using `string.h`, this project implements basic functionalities as a learning path.

## Project Structure 🧭

The project is structured in the following way.

```text
C-string-lib/
├── include/
│ ├── dstring_tests.h       // Test functions for the dstring_t struct
│ ├── dstring_utils.h       // Actual util functions for the dstring_t struct (core)
│ ├── dtypes.h              // Definitions of data types
│ ├── env_parser_tests.h    // Test functions for the parser of the env file
│ ├── env_parser.h          // Function definitions for the parser of env file
│ ├── report.h              // Reporting functions for test results
│ ├── sexyness.h            // Well... look inside 😉
│ ├── string_tests.h        // Test functions for basic (char *) operations
│ ├── string_utils.h        // Actual util functions for (char *)
│ ├── template_tests.h      // Test functions for the templating logic
│ └── template.h            // Actual util functions for the tamplating logic
├── src/
│ ├── dstring_utils.c
│ ├── env_parser.c
│ ├── string_utils.c
│ └── template.c
├── tests/
│ ├── dstring_tests.c
│ ├── env_parser_tests.c
│ ├── main.c                // Invocations of the tests
│ ├── report.c
│ ├── sexyness.c
│ ├── string_tests.c
│ └── tempalte_tests.c
└── Makefile                // Bob the builder right here 👷
```

## Functionalities ⚙️

You might say "Wow Marco, this project contains so many cool things 🤩" but wait! There's more!

To really dive into the magic of strings in C, the below gives an overview of the functions implemented in the project.

### Utility Functions (char *)

- `str_length`: Get the length of a string
- `str_equal`:  Compare two strings for equality
- `str_copy`:   Copy one string to another
- `str_find`:   Find a substring (the needle) in a string (the haystack) and return a pointer to the first char of the occurrence if present
- `str_count`:  Count the number of occurrences of a substring in a given string
- `str_split`:  Split a string at a given substring and return a list of the resulting pieces (the famous pointer to pointer!)

### New dstring_t Functions

- `dstring_init`:       Create a *dstring_t* instance based on a given char * string that it should contain
- `dstring_from_file`:  Create a *dstring_t* instance from a file, given a file path
- `dstring_free`:       Properly free a given *dstring_t* and the containing string (No dangling pointers allowed in this house!)
- `dstring_set`:        Set the value of the string contained in the *dstring_t* instance to a given (char *)
- `dstring_append`:     Append a string to the given *dstring_t* instance, accounting for length, capacity, and a potential reallocation
- `dstring_reverse`:    Reverse a *dstring_t*
- `dstring_to_upper`:   Convert all chars in the given *dstring_t* content to uppercase
- `dstring_to_lower`:   Convert all chars in the given *dstring_t* content to lowercase
- `dstring_trim`:       Remove all leading and trailing whitespaces from the given string
- `dstring_replace`:    Replace a given substring in the string with a new substring
- `dstring_insert`:     Insert a given substring into the dstring's data after a given index

### Template-Parser

The functions mentioned above are used in a template parser, that enables the user to fill in certain vailes into a defined template 📝.

**Example:**

Given the template

```text
Hello {{name}}, I am contacting you regarding {{topic}}.
```

we can apply the `template_apply` function using the map 🗺️

```text
name = "Bob"
topic = "our C project"
```

to obtain the final text

```text
Hello Bob, I am contacting you regarding our C project.
```

### Env-Parser

To efficiently create a larger key-value map for the template parser, a parser for env files is implemented that parses the following structure.

```text
KEY1=VALUE1
KEY2=VALUE2
...
```

This can e.g. be invoked together with the tempalte parser and the method `dstring_from_file`, to process larger files 🚀.

## How to build 🏗️

To build the project using the `make` utility, execute the following.

```bash
make
make clean
./test
```

Have fun and happy coding! 🥳🎉

## License 📜

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
