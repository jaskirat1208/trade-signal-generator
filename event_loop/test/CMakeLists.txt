include_directories(${GTEST_INCLUDE_DIRS})

add_executable(eventloop_test test_eventloop.cpp)

target_link_libraries(eventloop_test eventloop gtest gtest_main pthread)