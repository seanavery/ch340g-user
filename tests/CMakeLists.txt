# Set the test source files
set(TEST_SOURCES
    test_ch340g.cpp
)

# Create the test executable
add_executable(test_ch340g ${TEST_SOURCES})

# Add include directory
target_include_directories(test_ch340g PRIVATE ../)

# Link against the ch340g library
target_link_libraries(test_ch340g PRIVATE ch340g)

# Add any additional dependencies
# target_link_libraries(test_ch340g PRIVATE <dependency1> <dependency2> ...)

# Add the test target
add_test(NAME ch340g_test COMMAND test_ch340g)
