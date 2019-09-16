add_library(App STATIC
    src/AMainLoop.cpp
    src/Bomberman.cpp
    src/Input.cpp
    src/Menu.cpp
)

target_link_libraries(App
    sfml-graphics
    sfml-window
    sfml-system
    Engine
    Renderer
    Models
)

add_executable(bomberman src/main.cpp)
target_link_libraries(bomberman App)

set(MODELS_DIR ${PROJECT_SOURCE_DIR}/renderer/res/models)
target_compile_definitions(App PRIVATE MODELS_DIR=\"${MODELS_DIR}\")

# Create a macro that refers to the settings direcory
set(SETTINGS_DIR "${CMAKE_BINARY_DIR}/settings")
file(MAKE_DIRECTORY ${SETTINGS_DIR})
add_compile_definitions(SETTINGS_DIR=\"${SETTINGS_DIR}\")

# Manage dependency: cereal
include(FetchContent)

FetchContent_Declare(
  cereal
  GIT_REPOSITORY https://github.com/USCiLab/cereal
  GIT_TAG        v1.2.2
)

FetchContent_Populate(cereal)

target_include_directories(App PUBLIC ${cereal_SOURCE_DIR}/include)
