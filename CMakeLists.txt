# see <https://cliutils.gitlab.io/modern-cmake/chapters/basics.html#minimum-version>
cmake_minimum_required(VERSION 3.15...3.25)

project(example_json_read
            DESCRIPTION "Demonstrates the use of an external library to read a JSON document."
            LANGUAGES C)

add_compile_options(-Wall -Wextra)

add_library(cjson STATIC src/cjson/cJSON.c)
target_include_directories(cjson PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/cjson")

add_executable(main src/main.c)
target_link_libraries(main PRIVATE cjson)
