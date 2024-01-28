cmake_minimum_required(VERSION 3.0.0)

project(Space_Explorer)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/glad.c
)

add_subdirectory(include/glfw)

target_include_directories(${PROJECT_NAME} 
    PUBLIC include/glfw/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} 
    glfw
)