cmake_minimum_required (VERSION 3.0)
project (cg1_s70357_2017)

set(CMAKE_CXX_STANDARD 11)

find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_package(FreeImage REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${FreeImage_INCLUDE_DIRS})

set (PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set (PROJECT_SHADER_DIR ${PROJECT_SOURCE_DIR}/shader)

set (shader_files
        Dreiecke.fs
        Dreiecke.vs
        )

include_directories("${PROJECT_BINARY_DIR}")
link_directories(${freeglut_STATIC_LIBRARY_DIRS})

foreach(resource ${shader_files})
    configure_file(${PROJECT_SHADER_DIR}/${resource} ${resource} COPYONLY)
endforeach()

add_executable(triangle ${PROJECT_SOURCE_DIR}/main.cc ${PROJECT_SOURCE_DIR}/LoadShader.cpp)
target_link_libraries(triangle ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} ${FreeImage_LIBRARIES})

enable_testing()
add_subdirectory(test)