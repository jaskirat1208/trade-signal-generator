cmake_minimum_required(VERSION 3.15)

add_library(eventloop INTERFACE)

target_include_directories(eventloop INTERFACE include/)
target_compile_features(eventloop INTERFACE cxx_std_17)

enable_testing()
add_subdirectory(test)