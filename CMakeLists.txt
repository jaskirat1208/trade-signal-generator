cmake_minimum_required(VERSION 3.12.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)   
# set the project name
project(trading-platform)

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

find_package(GTest)
if (GTEST_FOUND)
	message("Gtest Already installed")
else (GTEST_FOUND)
	message("Installing gtest")
	# include(externals/gtest.cmake)
endif (GTEST_FOUND)
# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/trade-signal-generator)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/build/docs)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)


# add the executable
add_subdirectory(event_loop)
add_subdirectory(platform)
add_subdirectory(strategy)
add_subdirectory(externals/gtest)
