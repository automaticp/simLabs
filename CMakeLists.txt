cmake_minimum_required(VERSION 3.16...3.22)

project(simLabs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(distribution)
add_subdirectory(histogram)
add_subdirectory(simulation)

# Why this has to be INTERFACE? What does this do? What am I doing?
#target_compile_definitions(histogram INTERFACE USE_DISTRIBUTION)


add_executable(simLabs "main.cpp")

# enables use of 'distribution' with 'histogram'
target_compile_definitions(simLabs PRIVATE USE_DISTRIBUTION)

target_link_libraries(simLabs PRIVATE distribution histogram simulation)
