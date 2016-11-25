file(GLOB_RECURSE SOURCE_FILES
    "src/*.cpp"
    "src/*.h"
    "src/*.hpp"
    )

add_library(Auris STATIC ${SOURCE_FILES})
target_link_libraries(Auris ${EXTRA_LIBS})

install(TARGETS Auris EXPORT AurisConfig
    ARCHIVE  DESTINATION lib
    LIBRARY  DESTINATION lib
    RUNTIME  DESTINATION bin) #for windows
install(DIRECTORY ../include/ DESTINATION include)

install(EXPORT AurisConfig DESTINATION share/Auris/cmake)

export(TARGETS Auris FILE AurisConfig.cmake)
