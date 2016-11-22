file(GLOB_RECURSE SOURCE_FILES
    "src/*.cpp"
    "src/*.h"
    "src/*.hpp"
    )

add_library(Auris STATIC ${SOURCE_FILES})
target_link_libraries(Auris ${EXTRA_LIBS} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SRE_LIBRARY} ${BOX2D_LIBRARY} ${Pdh_LIBRARY})
