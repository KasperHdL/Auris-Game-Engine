cmake_minimum_required(VERSION 3.6)
project(AurisProject CXX)

IF(UNIX)
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

    IF(CMAKE_BUILD_TYPE MATCHES Debug)
        set(DEBUG_MODE TRUE)
    ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
        set(DEBUG_MODE FALSE)
    ENDIF()
ELSE(UNIX)
    set(DEBUG_MODE TRUE)
ENDIF(UNIX) 

IF(DEBUG_MODE)
    message("----- Debug Build -----")
    add_definitions(-DDEBUG)
ELSE()
    message("----- Release Build -----")
ENDIF()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

#########################################################
# FIND OPENGL
#########################################################
IF(APPLE)
    INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
    MARK_AS_ADVANCED (OpenGL_LIBRARY)
    SET(EXTRA_LIBS ${OpenGL_LIBRARY})
ELSE (APPLE)
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})
    IF(UNIX)
        find_package(GLEW REQUIRED)
    ELSE(UNIX)
        find_package(glew REQUIRED)
        SET(EXTRA_LIBS ${EXTRA_LIBS} pdh.lib)
    ENDIF(UNIX)
    include_directories(${GLEW_INCLUDE_DIR})
    SET(EXTRA_LIBS ${EXTRA_LIBS} ${OPENGL_LIBRARY} ${GLEW_LIBRARY})
ENDIF (APPLE)
 
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_IMAGE REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

find_package(SDL2_MIXER REQUIRED)
include_directories(${SDL2_MIXER_INCLUDE_DIRS})

# Box2D
find_package(Box2D REQUIRED)
include_directories(${BOX2D_INCLUDE_DIR})

#SRE
find_package(SRE REQUIRED)
include_directories(${SRE_INCLUDE_DIR})

include_directories(include)

SET(EXTRA_LIBS ${EXTRA_LIBS} ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${BOX2D_LIBRARY} ${SRE_LIBRARY})

add_subdirectory(Auris)
add_subdirectory(Game)
add_subdirectory(Demos)
