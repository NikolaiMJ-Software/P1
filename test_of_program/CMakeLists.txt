# Create an executable for your test case (this is an executable, not a library)
add_executable(run_test run_test.c
        PLPR_TestCase.c
        scan_data_TestCase.c
        BC_TestCase.c
        STV_TestCase.c)

# Link the executable to necessary libraries (e.g., math library, if needed)
target_link_libraries(run_test m)

# Register the test with CTest (so it can be run as part of CMake's testing framework)
add_test(NAME run_test COMMAND run_test)

# Link the test executable to the necessary source files from the main project
target_sources(run_test PRIVATE
        ../US_election_data/scan_data.c
                ../connecter.h
        ../Features/Wyoming_Rule.c
                ../election_systems/STV.c
                ../election_systems/BC.c)
#target_sources(run_test PRIVATE ../wyoming_rule.c )
