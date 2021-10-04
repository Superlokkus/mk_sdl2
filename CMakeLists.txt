cmake_minimum_required(VERSION 3.19)
project(cg1_s70357_2017 VERSION 1.0)

add_subdirectory(${PROJECT_SOURCE_DIR}/mk_sdl2)

set(prakt_sdl_main_src
        src/main.cpp)

add_executable(${PROJECT_NAME} ${prakt_sdl_main_src})
set_property(TARGET ${PROJECT_NAME} PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(${PROJECT_NAME} mk_sdl2)
