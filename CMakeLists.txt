cmake_minimum_required (VERSION 3.0)
project (cg1_s70357_2017)

set(CMAKE_CXX_STANDARD 11)

set (PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory(${PROJECT_SOURCE_DIR}/mk_graphics)

set(prakt_sdl_main_src
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/exercises.cpp
        ${PROJECT_SOURCE_DIR}/exercises.hpp
        )

add_executable(prakt_sdl_main ${prakt_sdl_main_src})
target_link_libraries(prakt_sdl_main ${mk_graphics})

set(TEST_ENABLED TRUE CACHE BOOL "Tests are enabled")
if (${TEST_ENABLED})
enable_testing()
add_subdirectory(test)
endif()

