cmake_minimum_required(VERSION 3.16...3.22)

file(GLOB_RECURSE distribution_FILES CONFIGURE_DEPENDS *.h *.cpp *.inl)

add_library(distribution STATIC ${distribution_FILES})

target_include_directories(distribution PUBLIC .)
# enables use of 'distribution' with 'histogram'
target_compile_definitions(distribution PUBLIC USE_DISTRIBUTION)
