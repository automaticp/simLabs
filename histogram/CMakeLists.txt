cmake_minimum_required(VERSION 3.16...3.22)

add_library(histogram INTERFACE "Histogram.h")
target_include_directories(histogram INTERFACE .)