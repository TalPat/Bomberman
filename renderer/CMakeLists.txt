find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED sfml-all)
pkg_check_modules(ASSIMP REQUIRED assimp)
pkg_check_modules(GLM REQUIRED glm)
pkg_check_modules(GLEW REQUIRED glew)

add_library(Renderer STATIC
    src/Renderer.cpp
    src/Camera.cpp
    src/Model.cpp
    src/Shader.cpp
    src/Mesh.cpp
)

include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Renderer ${SFML_LIBRARIES})
include_directories(${GLM_INCLUDE_DIRS})
target_link_libraries(Renderer ${GLM_LIBRARIES})
include_directories(${ASSIMP_INCLUDE_DIRS})
target_link_libraries(Renderer ${ASSIMP_LIBRARIES})
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(Renderer ${GLEW_LIBRARIES})