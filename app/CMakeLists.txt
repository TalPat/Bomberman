add_library(App STATIC
    src/AMainLoop.cpp
    src/Bomberman.cpp
    src/Input.cpp
)

target_link_libraries(App
    sfml-graphics
    sfml-window
    sfml-system
    Engine
    Renderer
    Models
    pthread
)

if(NOT APPLE)
target_link_libraries(App
    X11
)
endif()

add_executable(bomberman src/main.cpp)
target_link_libraries(bomberman App)
