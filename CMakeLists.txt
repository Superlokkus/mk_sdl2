cmake_minimum_required(VERSION 3.19)
project(test_sdl2 VERSION 1.0)

add_subdirectory(${PROJECT_SOURCE_DIR}/mk_sdl2)

add_executable(vulcan_test src/vulcan_test.cpp)
set_property(TARGET vulcan_test PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET vulcan_test PROPERTY CXX_STANDARD 20)
target_link_libraries(vulcan_test mk_sdl2)

add_executable(draw_test src/draw_test.cpp)
set_property(TARGET draw_test PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET draw_test PROPERTY CXX_STANDARD 20)
target_link_libraries(draw_test mk_sdl2)


add_executable(audio_test src/audio_test.cpp)
set_property(TARGET audio_test PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET audio_test PROPERTY CXX_STANDARD 20)
target_link_libraries(audio_test mk_sdl2)
