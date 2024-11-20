# Create an executable for your test case (this is an executable, not a library)
add_executable(Scan_Data_TestCase Scan_Data_TestCase.c)

# Link the executable to necessary libraries (e.g., math library, if needed)
target_link_libraries(Scan_Data_TestCase m)

# Register the test with CTest (so it can be run as part of CMake's testing framework)
add_test(NAME Scan_Data_TestCase COMMAND Scan_Data_TestCase)

# Link the test executable to the necessary source files from the main project
target_sources(Scan_Data_TestCase PRIVATE ../scan_data.c ../connecter.h)
