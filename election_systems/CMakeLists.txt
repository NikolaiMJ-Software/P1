
# Link the executable to necessary libraries (e.g., math library, if needed)
target_link_libraries(PLPR STV BC m)

# Register the test with CTest (so it can be run as part of CMake's testing framework)
#add_test(NAME Scan_Data_TestCase COMMAND Scan_Data_TestCase)

# Link the test executable to the necessary source files from the main project
target_sources(P1 PRIVATE ../winner_of_election.c ../connecter.h)
