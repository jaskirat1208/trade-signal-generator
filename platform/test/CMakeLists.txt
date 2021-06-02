find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(platform_test run.cpp)

target_link_libraries(platform_test platform ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARY} pthread)
# target_link_libraries(platform_test ${GTEST_LIBRARY_DEBUG} ${GTEST_MAIN_LIBRARY_DEBUG})
