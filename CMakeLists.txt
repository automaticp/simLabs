cmake_minimum_required(VERSION 3.16...3.22)

project(simLabs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(distribution)
add_subdirectory(histogram)
add_subdirectory(simulation)

add_executable(simLabs "main.cpp")

target_link_libraries(simLabs PRIVATE distribution histogram simulation)
