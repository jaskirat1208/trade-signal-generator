cmake_minimum_required(VERSION 3.12.0)

include_directories(platform INTERFACE include/)
add_library(strategy src/sma_strategy.cpp src/sma_queue.cpp)

target_link_libraries(strategy platform eventloop)

add_subdirectory(test)