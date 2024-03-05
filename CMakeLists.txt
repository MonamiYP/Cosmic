cmake_minimum_required(VERSION 3.5.0)

project(Space_Explorer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE IMGUI include/imgui/*.cpp)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/glad.c
    ${IMGUI}
    ${SOURCE_FILES}
)

add_subdirectory(include/glfw)
add_subdirectory(include/assimp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC include/glfw/include
    PUBLIC include/assimp/include
    PUBLIC res
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/entities
)

target_link_libraries(${PROJECT_NAME} 
    glfw
    assimp
)