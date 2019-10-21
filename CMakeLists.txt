cmake_minimum_required(VERSION 3.0)

project(nibbler)
set(CMAKE_CXX_STANDARD 17)

if(APPLE)
    include_directories(
        ~/.brew/include
        /usr/local/Cellar/sfml/2.5.1/include
		/usr/local/Cellar/assimp/4.1.0/include
		/usr/local/Cellar/glew/2.1.0/include
		/usr/local/Cellar/glm/0.9.9.5/include
        )
    link_directories(
        ~/.brew/lib
        /usr/local/lib
    )
endif()

include_directories(
    engine/include
    renderer/include
    sound/include
    models/include
    app/include
)

add_subdirectory(engine)
add_subdirectory(renderer)
add_subdirectory(sound)
add_subdirectory(models)
add_subdirectory(app)
