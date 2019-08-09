cmake_minimum_required(VERSION 3.0)

project(nibbler)
set(CMAKE_CXX_STANDARD 20)

if(APPLE)
    include_directories(~/.brew/include)
    link_directories(~/.brew/lib)
endif()

include_directories(
    engine/include
    renderer/include
    models/include
)

add_subdirectory(engine)
add_subdirectory(renderer)
add_subdirectory(models)
add_subdirectory(app)
