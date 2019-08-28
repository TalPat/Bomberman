cmake_minimum_required(VERSION 3.0)

project(nibbler)
set(CMAKE_CXX_STANDARD 17)

if(APPLE)
    include_directories(
        ~/.brew/include
        /usr/local/Cellar/sfml/2.5.1/include
        )
    link_directories(
        ~/.brew/lib
        /usr/local/lib
    )
endif()

include_directories(
    engine/include
    renderer/include
    models/include
    app/include
)

add_subdirectory(engine)
add_subdirectory(renderer)
add_subdirectory(models)
add_subdirectory(app)
