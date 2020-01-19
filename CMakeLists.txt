cmake_minimum_required(VERSION 3.15)
project(Chip8)

set(CMAKE_CXX_STANDARD 14)

# Include sub-projects.
#set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML COMPONENTS system graphics window audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
add_executable(Chip8 chip8.cpp CPU.h CPU.cpp)
target_link_libraries(Chip8 sfml-graphics sfml-window sfml-system sfml-audio)