cmake_minimum_required(VERSION 3.6)
project(Auris CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
   
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

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
        SET(EXTRA_LIBS pdh.lib)
    ENDIF(UNIX)
    include_directories(${GLEW_INCLUDE_DIR})
    SET(EXTRA_LIBS ${OPENGL_LIBRARY} ${GLEW_LIBRARY})
ENDIF (APPLE)

find_package(SDL2_IMAGE REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(.)

# Box2D
find_package(Box2D REQUIRED)
include_directories(${BOX2D_INCLUDE_DIR})

find_package(SRE REQUIRED)

if (SRE_FOUND)
    include_directories(${SRE_INCLUDE_DIR})
ELSE (SRE_FOUND)
    MESSAGE( STATUS "Failed to find Simple Render Engine")
endif(SRE_FOUND)

include_directories(src)

file(GLOB_RECURSE SOURCE_FILES
    "src/*.cpp"
    "src/*.h"
    "src/*.hpp"
    )

add_library(Auris STATIC ${SOURCE_FILES})
target_link_libraries(Auris ${EXTRA_LIBS} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SRE_LIBRARY} ${BOX2D_LIBRARY} ${Pdh_LIBRARY})

install(TARGETS Auris DESTINATION lib)
install(DIRECTORY src/ DESTINATION include)

