cmake_minimum_required(VERSION 3.5.0)

project(Space_Explorer)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE IMGUI lib/imgui/*.cpp)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/openGL/glad.c
    ${IMGUI}
    ${SOURCE_FILES}
)

add_subdirectory(lib/glfw)
add_subdirectory(lib/assimp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC lib/glfw/include
    PUBLIC lib/assimp/include
    PUBLIC res
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/ECS
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Engine
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Objects
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/OpenGL
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Scenes
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Util
)

target_link_libraries(${PROJECT_NAME} 
    glfw
    assimp
)