cmake_minimum_required(VERSION 3.16...3.22)

add_library(simulation STATIC Simulation.h Simulation.cpp)

target_include_directories(simulation PUBLIC .)
target_link_libraries(simulation PRIVATE distribution)