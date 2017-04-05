# Set source files root directory
set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

# Autodetect all *.cpp source files
file(GLOB_RECURSE SOURCE_LIST "*.cpp")

# All source files
set(SRC ${SOURCE_LIST})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED COMPONENTS System Window Graphics)
find_package(Box2D REQUIRED)

#set headers stuff
set(INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/vehicle
        ${PROJECT_SOURCE_DIR}/src/Entity
        ${SFML_INCLUDE_DIR}
        ${BOX2D_INCLUDE_DIR}/Box2D
        )

#set lib stuff
set(DEPEND_LIBS
        ${SFML_LIBRARIES}
        ${BOX2D_LIBRARY}
        )

include_directories(${INCLUDE_DIRS})
message(${SRC})
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${DEPEND_LIBS})
