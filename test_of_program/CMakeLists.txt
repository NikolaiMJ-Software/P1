add_executable(Scan_Data_TestCase Scan_Data_TestCase.c)

# Link the test executable to your source files
target_link_libraries(Scan_Data_TestCase
        connecter.c
        m
)

# Register the test with CTest
add_test(NAME Scan_Data_TestCase COMMAND Scan_Data_TestCase)
