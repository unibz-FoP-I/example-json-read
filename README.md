# JSON parsing example

Example of parsing a JSON document using the [cJSON](https://github.com/DaveGamble/cJSON) library.

To compile the example you need [CMake](https://cmake.org/):

```bash
$ cmake -B build
$ cmake --build build
```

The executable will be in the `build/main` file. The JSON document can be read from the standard input (no arguments) of from a file.