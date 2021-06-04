include_directories(${GTEST_INCLUDE_DIRS})

add_executable(platform_test run.cpp)

target_link_libraries(platform_test platform ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARY} pthread)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})