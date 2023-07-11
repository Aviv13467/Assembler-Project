cmake_minimum_required(VERSION 3.25)
project(new C)

set(CMAKE_C_STANDARD 90)

add_executable(new preprocessor.c hashtable.h utils.h includes.h main.c preprocessor.h)
