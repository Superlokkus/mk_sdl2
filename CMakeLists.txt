cmake_minimum_required(VERSION 3.19)
project(cg1_s70357_2017 VERSION 1.0)

find_package(SDL2 REQUIRED)

set(prakt_sdl_main_src
        src/main.cpp
        src/sdl2_opengl_helper.cpp
        src/sdl2_opengl_helper.hpp
        )

add_executable(${PROJECT_NAME} ${prakt_sdl_main_src})
set_property(TARGET ${PROJECT_NAME} PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)
