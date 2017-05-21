# Set source files root directory
set(SRCROOT ${PROJECT_SOURCE_DIR}/src)
# Autodetect all *.cpp source files
file(GLOB_RECURSE SOURCE_LIST "${PROJECT_SOURCE_DIR}/src/*.cpp")

# All source files
set(SRC ${SOURCE_LIST})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED COMPONENTS System Graphics Window)
find_package(Box2D REQUIRED)

#set headers stuff
set(INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/src/Interfaces
        ${PROJECT_SOURCE_DIR}/src/Maps
        ${PROJECT_SOURCE_DIR}/src/Modules
        ${PROJECT_SOURCE_DIR}/src/Managers
        ${PROJECT_SOURCE_DIR}/src/Objects
        ${PROJECT_SOURCE_DIR}/src/Objects/GameObjects/
        ${PROJECT_SOURCE_DIR}/src/Objects/GameObjects/Vehicle
        ${PROJECT_SOURCE_DIR}/src/Scene
        ${PROJECT_SOURCE_DIR}/src/Graphics/Textures
        ${PROJECT_SOURCE_DIR}/src/Tools
        ${PROJECT_SOURCE_DIR}/src/Utils
        ${PROJECT_SOURCE_DIR}/src/Events
        ${PROJECT_SOURCE_DIR}/src/Graphics
        ${PROJECT_SOURCE_DIR}/src/Graphics/UI
        ${PROJECT_SOURCE_DIR}/src/Activity
        ${PROJECT_SOURCE_DIR}/src/Game
        ${PROJECT_SOURCE_DIR}/src/Game/CheckPoint
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
