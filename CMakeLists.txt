cmake_minimum_required(VERSION 3.18)
project(wordle)
find_package(Threads)
find_package(Git QUIET)

# Set compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -pedantic-errors -g")

# Define all testing related content here
enable_testing()

# Bring in GoogleTest
include(FetchContent)
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929  # release-1.11.0
        )
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()
include_directories(${googletest_SOURCE_DIR}/googletest/include)

# Include project headers
include_directories(./include)
# Define the source files and dependencies for the executable
set(SOURCE_FILES
        src/Game.cpp
        src/Guess.cpp
        tests/wordleTests.cpp
        main.cpp
        )

set(RUN_FILES
        include/Game.h
        include/Guess.h
        src/Game.cpp
        src/Guess.cpp
        main.cpp)

add_executable(RUN ${RUN_FILES})

# Make the project root directory the working directory when we run
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_executable(testing ${SOURCE_FILES})
add_dependencies(testing gtest)
target_link_libraries(testing gtest ${CMAKE_THREAD_LIBS_INIT})