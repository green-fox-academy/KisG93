cmake_minimum_required(VERSION 3.13)
project(median C)

set(CMAKE_C_STANDARD 99)

add_executable(median main.c median.c median.h)