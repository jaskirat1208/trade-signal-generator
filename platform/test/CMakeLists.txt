include_directories(${GTEST_INCLUDE_DIRS})

add_executable(platform_test run.cpp)

target_link_libraries(platform_test platform gtest gtest_main pthread)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})