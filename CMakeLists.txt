cmake_minimum_required(VERSION 3.16)
project(ch340)

set(CMAKE_CXX_STANDARD 11)

# Add the source files
set(SOURCES
    ch340.cpp
    ch340.h
)

# create shared library
add_library(ch340 SHARED ${SOURCES})
set_target_properties(ch340 PROPERTIES VERSION 0.0.1)
# create static library
add_library(ch340_static STATIC ${SOURCES})

target_link_directories(
    ch340
    PUBLIC
    "/lib/x86_64-linux-gnu")

target_link_directories(
    ch340_static
    PUBLIC
    "/lib/x86_64-linux-gnu")

# Link against libusb
target_link_libraries(ch340 PUBLIC -lusb-1.0)
target_link_libraries(ch340_static PUBLIC -lusb-1.0)


# Install shared library
install(TARGETS ch340
        LIBRARY DESTINATION /usr/local/lib
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)

# Install static library
install(TARGETS ch340_static
        ARCHIVE DESTINATION /usr/local/lib
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)

# Install header files
install(FILES ch340.h DESTINATION /usr/local/include)

# Include the tests directory
add_subdirectory(tests)
