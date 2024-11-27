cmake_minimum_required(VERSION 3.29)
project(P1 C)

set(CMAKE_C_STANDARD 11)

add_executable(P1 main.c
        connecter.h
        scan_data.c
        winner_of_election.c
        election_systems/electoral_college.c
        election_systems/PLPR.c
        election_systems/STV.c
        election_systems/BC.c
        monte_carlo.c
        Wyoming_Rule.c
        available_files.c
        Parameters.c
        scan_electors.c
)

# Add the test directory
add_subdirectory(test_of_program)