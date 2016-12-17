file(GLOB_RECURSE GAME_FILES
    "src/*.cpp"
    "src/*.hpp"
)

add_executable(Demo_ParticleSystem ${GAME_FILES})
target_link_libraries(Demo_ParticleSystem ${EXTRA_LIBS} Auris)

IF (WIN32)
    SET(SDL2_dll "" CACHE STRING "Where the SDL2.dll can be found")
    SET(SDL2_image_lib_path "" CACHE PATH "Where the SDL2_image.dll can be found")
	SET(SDL2_mixer_lib_path "" CACHE PATH "Where the SDL2_mixer.dll can be found")
    SET(DLLFileList "${SDL2_mixer_lib_path}/SDL2_mixer.dll" "${SDL2_image_lib_path}/SDL2_image.dll" "${SDL2_image_lib_path}/libjpeg-9.dll" "${SDL2_image_lib_path}/libpng16-16.dll" "${SDL2_image_lib_path}/libtiff-5.dll" "${SDL2_image_lib_path}/libwebp-4.dll" "${SDL2_image_lib_path}/zlib1.dll" ${SDL2_dll})
    file(COPY ${DLLFileList} DESTINATION Debug)
    file(COPY ${DLLFileList} DESTINATION Release)
	
	file(COPY data DESTINATION Debug)
	file(COPY data DESTINATION Release)

ELSE(WIN32)

	file(COPY data DESTINATION .)
	
ENDIF(WIN32)
