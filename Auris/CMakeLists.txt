file(GLOB_RECURSE SOURCE_FILES
    "src/*.cpp"
    )

#include_directories(../include)
add_library(Engine STATIC ${SOURCE_FILES})
target_link_libraries(Engine ${EXTRA_LIBS})

install(TARGETS Engine EXPORT AurisConfig
    ARCHIVE  DESTINATION lib
    LIBRARY  DESTINATION lib
    RUNTIME  DESTINATION bin) #for windows

install(DIRECTORY ../include/ DESTINATION include)

install(EXPORT AurisConfig DESTINATION share/Engine/cmake)

export(TARGETS Engine FILE AurisConfig.cmake)
