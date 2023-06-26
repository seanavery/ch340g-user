cmake_minimum_required(VERSION 3.26)
project(ch340g-user)

set(CMAKE_CXX_STANDARD 11)

# Add the source files
set(SOURCES
    ch340g.cpp
    ch340g.h
)

# Create the executable/library
add_library(ch340g_user ${SOURCES})

target_link_directories(
    ch340g_user
    PRIVATE "/lib/x86_64-linux-gnu")

# Link against libusb
target_link_libraries(ch340g_user PRIVATE libusb-1.0)
