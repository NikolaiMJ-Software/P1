cmake_minimum_required(VERSION 3.29)
project(P1 C)

set(CMAKE_C_STANDARD 11)

add_executable(P1 main.c
        connecter.h
        Scan_Data.c
        Scan_Data_TestCase.c
        Winner_of_election.c)
