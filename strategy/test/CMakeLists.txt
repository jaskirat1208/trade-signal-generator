find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(strategy_test run.cpp)

target_link_libraries(strategy_test strategy ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARY} pthread)

file(INSTALL  data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})