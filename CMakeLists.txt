cmake_minimum_required(VERSION 3.29)
project(P1 C)

set(CMAKE_C_STANDARD 11)

add_executable(P1 main.c
        connecter.h
        US_election_data/scan_data.c
        winner_of_election.c
        election_systems/electoral_college.c
        election_systems/PLPR.c
        election_systems/STV.c
        election_systems/BC.c
        Features/monte_carlo.c
        Features/Wyoming_Rule.c
        available_files.c
        election_systems/Custom.c
        Candidates/scan_candidates.c
        Features/Compare_table.c
        Features/weight_of_votes.c
        Features/abolish_states.c
        Features/printUSA.c
        Features/copy_systems_names.c
        Features/format_number.c
)

# Add the test directory
add_subdirectory(test_of_program)