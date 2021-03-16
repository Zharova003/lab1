cmake_minimum_required(VERSION 3.17)
project(Yanalab C)

set(CMAKE_C_STANDARD 11)

add_executable(Yanalab main.c matrix.c matrix.h CException.c CException.h)