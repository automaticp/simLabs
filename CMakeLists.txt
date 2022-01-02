cmake_minimum_required(VERSION 3.16...3.22)

project(simlabs)

add_subdirectory(distribution)
add_subdirectory(histogram)
add_subdirectory(simulation)

add_executable(simlabs "main.cpp")

target_compile_features(simlabs PRIVATE cxx_std_17)

target_link_libraries(simlabs PRIVATE distribution histogram simulation)
