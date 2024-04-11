# Set the test source files
set(TEST_SOURCES
    test_ch340.cpp
)

# Create the test executable
add_executable(test_ch340 ${TEST_SOURCES})

# Add include directory
target_include_directories(test_ch340 PRIVATE ../)

# Link against the ch340 library
target_link_libraries(test_ch340 PRIVATE ch340)

# Add any additional dependencies.
# target_link_libraries(test_ch340g PRIVATE <dependency1> <dependency2> ...)

# Add the test target
add_test(NAME ch340_test COMMAND test_ch340)
