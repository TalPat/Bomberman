
add_library(Renderer STATIC
    src/Renderer.cpp
)

target_link_libraries(Renderer
    sfml-graphics
    sfml-window
    sfml-system
    Engine 
)

add_executable(bombermans src/main.cpp)
target_link_libraries(bombermans Renderer)
