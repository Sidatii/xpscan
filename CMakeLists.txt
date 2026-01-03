cmake_minimum_required(VERSION 3.10)
project(XP-SCAN)

set(CMAKE_CXX_STANDARD 17)

# Look for threads
find_package(Threads REQUIRED)

# Include directories
include_directories(include)

# Source files
add_executable(xpscan src/main.cpp src/Scanner.cpp src/Exporter.cpp src/Printer.cpp)

# Link pthread
target_link_libraries(xpscan PRIVATE Threads::Threads)
