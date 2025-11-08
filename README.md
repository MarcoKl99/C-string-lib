# C-string-lib - Utilities to work with Strings in C (+ Template-CLI)! 🚀

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

Welcome to this small project on a few implementations of utilites regarding Strings in C!

**Bonus:** A small templating CLI has been implemented, as described in the lower part of this file! This serves as a small example use-case for the implemented string functionalities.

## Sumamry 🏎️

The project consists of

- Utility functions on strings represented as `char *`
- Utility functions on strings represented as `dstring_t` to manage dynamic memory allocation
- Tests of the implemented functions
- Small CLI to dynamically fill placeholders in templates

The implementations of utility functions for performing basic string operations provide a groundwork for the main capability of populating templates following the pattern of `{{param}}` based on an env file, providing values for the used parameters. To invoke the templating tool, a small CLI `templater` is implemented, that takes as an input a path to a template file and a path to an env file and (optionally) saves the results to an output file. Details of the usage can be seen in the sections below.

The foundation of this project, to dynamically work with strings, is a struct, storing a pointer to the data as well as the current length and capacity. Serving as a container, this pattern passes the *memory ownership* from the caller to the callee. When performing reallocations, the called function takes care of the required memory management and the main process continues to work with the container struct instance.

```c
typedef struct
{
    char *data;
    size_t length;
    size_t capacity;
} dstring_t;
```

The following outlines the functionalities in more detail.

## Functionalities ⚙️

The core functionality of the project consists of the following parts.

### Utility Functions (char *) 🔧

- `str_length`: Get the length of a string
- `str_equal`:  Compare two strings for equality
- `str_copy`:   Copy one string to another
- `str_find`:   Find a substring (the needle) in a string (the haystack) and return a pointer to the first char of the occurrence if present
- `str_count`:  Count the number of occurrences of a substring in a given string
- `str_split`:  Split a string at a given substring and return a list of the resulting pieces (the famous pointer to pointer!)
- `str_substr`: Get the substring of a given string, specified by a start- and end-index
- `str_to_upper`: Return a new string as the uppercase version of the given one
- `str_to_lower`: Return a new string as the lowercase version of the given one

### New dstring_t Functions ✨

- `dstring_init`:       Create a *dstring_t* instance based on a given char * string that it should contain
- `dstring_from_file`:  Create a *dstring_t* instance from a file, given a file path
- `dstring_free`:       Properly free a given *dstring_t* and the containing string (No dangling pointers allowed in this house!)
- `dstring_set`:        Set the value of the string contained in the *dstring_t* instance to a given (char *)
- `dstring_append`:     Append a string to the given *dstring_t* instance, accounting for length, capacity, and a potential reallocation
- `dstring_reverse`:    Reverse a *dstring_t*
- `dstring_to_upper`:   Convert all chars in the given *dstring_t* content to uppercase
- `dstring_to_lower`:   Convert all chars in the given *dstring_t* content to lowercase
- `dstring_trim`:       Remove all leading and trailing whitespaces from the given string
- `dstring_insert`:     Insert a given substring into the dstring's data after a given index
- `dstring_replace`:    Replace a given substring in the string with a new substring

### Template-Parser 🔎

The functions mentioned above are used in a template parser, that enables the user to fill in certain vailes into a defined template 📝.

**Example:**

Given the template

```text
Hello {{name}}, I am contacting you regarding {{topic}}.
```

we can invoke the `template_apply` function using the map 🗺️

```text
name = "Bob"
topic = "our C project"
```

to obtain the final text

```text
Hello Bob, I am contacting you regarding our C project.
```

### Env-Parser 🧩

To efficiently create a larger key-value map for the template parser, a parser for env files is implemented that parses the following structure.

```text
KEY1=VALUE1
KEY2=VALUE2
...
```

This can e.g. be invoked together with the tempalte parser and the method `dstring_from_file`, to process larger files 🚀.

### Template-CLI 💻

The provided CLI `tempalter` enables the user to populate templates of the form

```text
Hello {{name}}, this is a text that can be filled with

Normal parameters: {{param}}
Uppercase parameters: {{upper:param}}
Lowercase parameters: {{lower:param}}

Have fun!
```

With an environment file like the following.

```text
name=Peter
param=MyCrazyParameter
...
```

To invoke the cli (after compiling the project), simply invoke

```bash
./templater path/to/template path/to/env --out path/to/output
```

The program populates the template with the values found in the env-file and saves the result to the given output path. When no output path is provided, the result is simply printed to the terminal.

## Project Structure 🧭

The project is structured in the following way.

```text
C-string-lib/
├── cli/
│ └── main.c                // Entry point for cli application - fill templates from files
├── include/
│ ├── cli_utils.h           // Function definitions for the template cli
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
│ ├── cli_utils.c
│ ├── dstring_utils.c
│ ├── env_parser.c
│ ├── sexyness.c
│ ├── string_utils.c
│ └── template.c
├── tests/
│ ├── dstring_tests.c
│ ├── env_parser_tests.c
│ ├── main.c                // Invocations of the tests
│ ├── report.c
│ ├── string_tests.c
│ └── tempalte_tests.c
└── Makefile                // Bob the builder right here 👷
```

## How to build 🏗️

To build the project using the `make` utility, execute the following.

```bash
make
make clean
./test                                      # Execute tests
./templater path/to/template path/to/env    # Invoke templater CLI
```

## Goal 🎯

While certainly not winning an award 🏆, this project aims for deepening the understanding of concepts in C regarding Strings, represented as Arrays of Characters, toghether with structs, memory ownership, memory leaks, dangling pointers and many more! When working with this data structure, simple implementations show the basics of concepts such as

- String initialization and representation
- Boundaries and the special null terminator `\0`
- Allocation on the Stack vs. Heap
- Usage of pointers (the classic topic... 😉) and memory management
- Basic structure of small projects
- Compilation process using the Makefile

Without using `string.h`, this project implements basic functionalities as a learning path.

## License 📜

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

Have fun and happy coding! 🥳🎉
