# see <https://cliutils.gitlab.io/modern-cmake/chapters/basics.html#minimum-version>
cmake_minimum_required(VERSION 3.7...3.25)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(example_json_read
            DESCRIPTION "Demonstrates the use of an external library to read a JSON document."
            LANGUAGES C)

add_compile_options(-Wall -Wextra)

add_library(cjson STATIC src/cjson/cJSON.c)
target_include_directories(cjson PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/cjson")

add_executable(main src/main.c)
target_link_libraries(main PRIVATE cjson)