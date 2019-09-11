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
		X11
)

add_executable(bomberman src/main.cpp)
target_link_libraries(bomberman App)
