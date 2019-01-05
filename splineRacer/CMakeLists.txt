cmake_minimum_required(VERSION 2.8)

project(splineRacer)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)


# set the module path for "findLib.cmake"
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/")

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(Freetype REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
# set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS} glimac/include splineengine/include third-party/include)

set(FREETYPE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/third-party/include/freetype2)
link_directories(${FREETYPE_DIRECTORY})
include_directories(${FREETYPE_DIRECTORY})
find_library(freetype2 freetype2 ${FREETYPE_DIRECTORY})

set(ALL_LIBRARIES splineengine glimac ${GLEW_LIBRARY} ${OPENGL_LIBRARIES} ${SDL_LIBRARY} ${FREETYPE_LIBRARIES})

add_subdirectory(glimac)
add_subdirectory(splineengine)



# Compiler les tests
file(GLOB TP_DIRECTORIES "TP*")
foreach(TP ${TP_DIRECTORIES})
    add_subdirectory(${TP})
endforeach()

# Compiler le main global
file(GLOB MAIN "src")
add_subdirectory(${MAIN})
