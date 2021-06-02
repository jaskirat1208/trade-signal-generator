cmake_minimum_required(VERSION 3.15)

include_directories(platform INTERFACE include/)
add_library(platform src/event_handler.cpp)

target_compile_features(platform INTERFACE cxx_std_17)

enable_testing()
add_subdirectory(test)