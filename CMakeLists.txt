cmake_minimum_required (VERSION 3.0)
project (cg1_s70357_2017 VERSION 1.0)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/sdl2-cmake-scripts")

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIR})


set(prakt_sdl_main_src
        src/main.cpp
        src/sdl2_opengl_helper.cpp
        src/sdl2_opengl_helper.hpp
        src/opengl_helper.cpp
        src/opengl_helper.hpp
        src/exercises.cpp src/exercises.hpp)

add_executable(${PROJECT_NAME} ${prakt_sdl_main_src})
set_property(TARGET ${PROJECT_NAME} PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARY} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

