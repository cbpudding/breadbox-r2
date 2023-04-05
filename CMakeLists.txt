cmake_minimum_required(VERSION 3.5)

project(breadbox C)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(Lua REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PhysFS REQUIRED)
find_package(SDL2 REQUIRED)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(breadbox
    ${SOURCES}
    ${PROJECT_SOURCE_DIR}/lib/microui/src/microui.c
    ${PROJECT_SOURCE_DIR}/lib/ya_getopt/ya_getopt.c
)

target_include_directories(breadbox
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        ${PROJECT_SOURCE_DIR}/lib/microui/src
        ${PROJECT_SOURCE_DIR}/lib/plibsys/src
        ${PROJECT_SOURCE_DIR}/lib/ya_getopt
        ${LUA_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${PHYSFS_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR}
)

target_link_libraries(breadbox
    ${PROJECT_SOURCE_DIR}/lib/plibsys/libplibsysstatic.a
    ${LUA_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${PHYSFS_LIBRARY}
    ${SDL2_LIBRARIES}
)