file(GLOB_RECURSE SOURCE_FILES
    "src/*.cpp"
    "src/*.h"
    "src/*.hpp"
    )

add_library(Auris STATIC ${SOURCE_FILES})
target_include_directories(Auris PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/mylib>  # <prefix>/include/mylib
)
target_link_libraries(Auris ${EXTRA_LIBS})

install(TARGETS Auris EXPORT AurisConfig
    ARCHIVE  DESTINATION lib
    LIBRARY  DESTINATION lib
    RUNTIME  DESTINATION bin) #for windows
install(DIRECTORY src/ DESTINATION include)

install(EXPORT AurisConfig DESTINATION share/Auris/cmake)

export(TARGETS Auris FILE AurisConfig.cmake)
