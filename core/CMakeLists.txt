add_library(Core STATIC
    src/AMainLoop.cpp
    src/Bomberman.cpp
)

target_link_libraries(Core
    Engine 
    Renderer
)

add_executable(bomberman src/main.cpp)
target_link_libraries(bomberman Core)
