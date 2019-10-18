find_package(PkgConfig REQUIRED)
pkg_check_modules(SFMLAUDIO REQUIRED sfml-audio)

add_library(Sound STATIC
    src/Sound.cpp
)

include_directories(${SFMLAUDIO_INCLUDE_DIRS})
target_link_libraries(Sound ${SFMLAUDIO_LIBRARIES})

set(SOUNDRES_DIR \"${PROJECT_SOURCE_DIR}/sound/res\")
target_compile_definitions(Sound PUBLIC SOUNDRES_DIR=${SOUNDRES_DIR})