cmake_minimum_required(VERSION 3.10)
project(XP-SCAN)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES src/Scanner.cpp src/Exporter.cpp src/Printer.cpp)
set(TEST_SOURCES tests/ExporterTest.cpp tests/ScannerTest.cpp tests/PrinterTest.cpp)

# Find Criterion (Testing library)
find_package(PkgConfig REQUIRED)
pkg_check_modules(CRITERION REQUIRED criterion)

# Look for threads
find_package(Threads REQUIRED)

# Include directories
include_directories(include)

# Actual executable
add_executable(xpscan src/main.cpp ${SOURCES})
target_link_libraries(xpscan PRIVATE Threads::Threads)

# Tests runner
add_executable(xpscan_tests EXCLUDE_FROM_ALL ${TEST_SOURCES} ${SOURCES})
target_include_directories(xpscan_tests PRIVATE ${CRITERION_INCLUDE_DIRS})
target_link_libraries(xpscan_tests PRIVATE Threads::Threads ${CRITERION_LIBRARIES})

# Test target
add_custom_target(test 
    COMMAND ${CMAKE_MAKE_PROGRAM} xpscan_tests
    COMMAND ./xpscan_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
