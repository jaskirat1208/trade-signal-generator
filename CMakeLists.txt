cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)   
# set the project name
project(trading-platform)

# add the executable
add_subdirectory(event_loop)
add_subdirectory(platform)
add_subdirectory(strategy)
