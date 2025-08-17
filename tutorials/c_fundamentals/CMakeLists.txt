cmake_minimum_required(VERSION 3.16)
project(foundations C)

set(CMAKE_C_STANDARD 11)

# Output executables to build/pc
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../../build/pc)

include_directories(include)

add_executable(foundations
    main.c
    src/big_o.c
    src/math_utils.c
    src/bitwise_utils.c
)
