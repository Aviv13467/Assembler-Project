cmake_minimum_required(VERSION 3.25)
project(Maman14 C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ansi -pedantic")

add_executable(Maman14 preprocessor.c hashtable.h utils.h main.c preprocessor.h hashtable.c first_pass.h utils.c symbol_table.h symbol_table.c first_pass.c memory.c globals.h LinkedList.h LinkedList.c second_pass.c second_pass.h entry_table.c entry_table.h extern_table.c extern_table.h)
