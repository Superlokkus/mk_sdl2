cmake_minimum_required(VERSION 3.19)
project(test_sdl2 VERSION 1.0)

add_subdirectory(${PROJECT_SOURCE_DIR}/mk_sdl2)

add_executable(${PROJECT_NAME} src/main.cpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(${PROJECT_NAME} mk_sdl2)

add_executable(audio_test src/audio_test.cpp)
set_property(TARGET audio_test PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET audio_test PROPERTY CXX_STANDARD 20)

target_link_libraries(audio_test mk_sdl2)
