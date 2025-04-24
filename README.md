# JSON parsing example

Example of parsing a JSON document using the [cJSON](https://github.com/DaveGamble/cJSON) library.

To compile the example you need [CMake](https://cmake.org/):

## Build

```bash
cmake -S . -B build
cmake --build build
```

The executable will be in the `build/main` file.

## Run

The JSON document can be read from the standard input (no arguments) or from a file.

```bash
./build/main < tests/data/json_org_01.json
```
