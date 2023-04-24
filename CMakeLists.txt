cmake_minimum_required(VERSION 3.5)

project(breadbox C)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(PhysFS REQUIRED)
find_package(SDL2 REQUIRED)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(breadbox
    ${SOURCES}
    ${PROJECT_SOURCE_DIR}/lib/fast_obj/fast_obj.c
    ${PROJECT_SOURCE_DIR}/lib/mathc/mathc.c
)

target_include_directories(breadbox
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        ${PROJECT_SOURCE_DIR}/lib/fast_obj
        ${PROJECT_SOURCE_DIR}/lib/mathc
        ${OPENGL_INCLUDE_DIR}
        ${PHYSFS_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR}
)

target_link_libraries(breadbox
    m
    ${OPENGL_LIBRARIES}
    ${PHYSFS_LIBRARY}
    ${SDL2_LIBRARIES}
)