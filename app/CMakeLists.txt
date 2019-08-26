add_library(App STATIC
    src/AMainLoop.cpp
    src/Bomberman.cpp
    src/Input.cpp
)

target_link_libraries(App
    ${CONAN_LIBS}
    Engine
    Renderer
    Models
)

# Create a macro that refers to the settings direcory
set(SETTINGS_DIR "${CMAKE_BINARY_DIR}/settings")
file(MAKE_DIRECTORY ${SETTINGS_DIR})
add_compile_definitions(SETTINGS_DIR=\"${SETTINGS_DIR}\")

add_executable(bomberman src/main.cpp)
target_link_libraries(bomberman App)
