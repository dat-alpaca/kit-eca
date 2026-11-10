cmake_minimum_required(VERSION 3.10)
project(eca C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_executable(main "src/main.c" "src/config.c" "src/context.c")