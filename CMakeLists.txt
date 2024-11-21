cmake_minimum_required(VERSION 3.29)
project(P1 C)

set(CMAKE_C_STANDARD 11)

add_executable(P1 main.c
        connecter.h
        scan_data.c
        winner_of_election.c
        "electoral_college.c"
        STV.c
        BC.c
        PLPR.c
)

# Add the test directory
add_subdirectory(test_of_program)