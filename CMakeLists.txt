cmake_minimum_required(VERSION 3.5)

project(breadbox C)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(breadbox ${SOURCES})

target_include_directories(breadbox
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        ${OPENGL_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR}
)

target_link_libraries(breadbox
    ${OPENGL_LIBRARIES}
    ${SDL2_LIBRARIES}
)