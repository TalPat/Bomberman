find_package(PkgConfig REQUIRED)
pkg_check_modules(ASSIMP REQUIRED assimp)
pkg_check_modules(GLM REQUIRED glm)
pkg_check_modules(GLEW REQUIRED glew)

add_library(Renderer STATIC
    src/Renderer.cpp
    src/Camera.cpp
    src/Model.cpp
    src/Shader.cpp
    src/Mesh.cpp
    src/Animation.cpp
    src/Square.cpp
    src/Particle.cpp
    src/Swarm.cpp
    src/GuiChar.cpp
)

include_directories(${GLM_INCLUDE_DIRS})
target_link_libraries(Renderer ${GLM_LIBRARIES})
include_directories(${ASSIMP_INCLUDE_DIRS})
target_link_libraries(Renderer ${ASSIMP_LIBRARIES})
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(Renderer ${GLEW_LIBRARIES})
if (APPLE)
    target_link_libraries(Renderer "-framework OpenGL")
endif()

set(SHADER_DIR \"${PROJECT_SOURCE_DIR}/renderer/res/shaders\")
target_compile_definitions(Renderer PUBLIC SHADER_DIR=${SHADER_DIR})
set(MODEL_DIR \"${PROJECT_SOURCE_DIR}/renderer/res/models\")
target_compile_definitions(Renderer PUBLIC MODEL_DIR=${MODEL_DIR})
set(SPRITE_DIR \"${PROJECT_SOURCE_DIR}/renderer/res/sprites\")
target_compile_definitions(Renderer PUBLIC SPRITE_DIR=${SPRITE_DIR})
set(CHARACTER_DIR \"${PROJECT_SOURCE_DIR}/renderer/res/characters\")
target_compile_definitions(Renderer PUBLIC CHARACTER_DIR=${CHARACTER_DIR})