cmake_minimum_required(VERSION 3.15)

project(nibbler)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wextra -Werror -Wall)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

link_libraries(
    ${CONAN_LIBS}
)

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
