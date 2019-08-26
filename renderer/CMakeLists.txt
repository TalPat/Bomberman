
add_library(Renderer STATIC
    src/Renderer.cpp
)

if (APPLE)
    target_link_libraries(Renderer "-framework OpenGL")
endif()
