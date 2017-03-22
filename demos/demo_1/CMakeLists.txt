cmake_minimum_required(VERSION 3.5)

project(demo_1)

# define the build type
set(CMAKE_BUILD_TYPE Debug)

# Set version information in a config.h file
set(${PROJECT_NAME}_VERSION_MAJOR 1)
set(${PROJECT_NAME}_VERSION_MINOR 0)

# Set C++11 standard
set(CMAKE_CXX_STANDARD 11)
# Define the path of our additional CMake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-modules")

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/src/${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# add the subdirectories
add_subdirectory(src)