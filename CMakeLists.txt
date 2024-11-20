cmake_minimum_required(VERSION 3.29)
project(P1 C)

set(CMAKE_C_STANDARD 11)

add_executable(P1 main.c
        Scan_Data_TXT.h
        Scan_Data_TXT.c)
