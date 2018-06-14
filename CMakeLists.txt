cmake_minimum_required (VERSION 3.0)
project (cg1_s70357_2017)

set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/sdl2-cmake-scripts")

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIR})


set (PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set (PROJECT_SHADER_DIR ${PROJECT_SOURCE_DIR}/shader)

set (shader_files
        Dreiecke.fs
        Dreiecke.vs
        )

include_directories("${PROJECT_BINARY_DIR}")

foreach(resource ${shader_files})
    configure_file(${PROJECT_SHADER_DIR}/${resource} ${resource} COPYONLY)
endforeach()

set(prakt_sdl_main_src
        ${PROJECT_SOURCE_DIR}/main.cpp
        src/sdl2_opengl_helper.cpp
        src/sdl2_opengl_helper.hpp
        src/opengl_helper.cpp
        src/opengl_helper.hpp
        )

add_executable(prakt_sdl_main ${prakt_sdl_main_src})
target_link_libraries(prakt_sdl_main ${SDL2_LIBRARY} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

