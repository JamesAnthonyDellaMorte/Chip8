cmake_minimum_required(VERSION 3.15)
project(Chip8)

set(CMAKE_CXX_STANDARD 14)

# Include sub-projects.

if(NOT WIN32)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML COMPONENTS system graphics window audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
add_executable(Chip8 chip8.cpp CPU.h CPU.cpp)
target_link_libraries(Chip8 sfml-graphics sfml-window sfml-system sfml-audio)
else(WIN32)

set(SFML_STATIC_LIBRARIES TRUE)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1")

set(SFML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML)

 find_package(SFML COMPONENTS system graphics window audio REQUIRED)

add_executable(Chip8 chip8.cpp CPU.h CPU.cpp)
target_link_libraries(Chip8 sfml-graphics sfml-window sfml-system sfml-audio)
endif()