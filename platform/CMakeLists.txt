cmake_minimum_required(VERSION 3.15)

include_directories(platform INTERFACE include/)
add_library(platform src/event_handler.cpp)

target_include_directories(platform INTERFACE include/)
target_compile_features(platform INTERFACE cxx_std_17)
target_link_libraries(platform eventloop)

enable_testing()
add_subdirectory(test)