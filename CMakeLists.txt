cmake_minimum_required(VERSION 3.15)
project(Chip8)

set(CMAKE_CXX_STANDARD 14)

# Include sub-projects.
set(SFML_STATIC_LIBRARIES TRUE)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1")

set(SFML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML)

 find_package(SFML COMPONENTS system graphics window audio REQUIRED)

add_executable(Chip8 chip8.cpp CPU.h CPU.cpp)
target_link_libraries(Chip8 sfml-graphics sfml-window sfml-system sfml-audio)