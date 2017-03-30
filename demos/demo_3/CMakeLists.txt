cmake_minimum_required(VERSION 3.5)

project(demo_3)

# define the build type
set(CMAKE_BUILD_TYPE Debug)

# Set version information in a config.h file
set(${PROJECT_NAME}_VERSION_MAJOR 3)
set(${PROJECT_NAME}_VERSION_MINOR 0)

# Set C++11 standard
set(CMAKE_CXX_STANDARD 11)
# Define the path of our additional CMake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-modules")


# add the subdirectories
add_subdirectory(src)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
#    add_custom_target(doc
#            ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
#            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#            COMMENT "Generating API documentation with Doxygen" VERBATIM
#            )
endif(DOXYGEN_FOUND)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/src/${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
