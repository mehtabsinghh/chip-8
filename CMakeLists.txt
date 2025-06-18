cmake_minimum_required(VERSION 3.10)
project(Chip-8)
# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Find SDL2 package
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable
add_executable(chip8 ${SOURCES})

# Link SDL2 library
target_link_libraries(chip8 ${SDL2_LIBRARIES})