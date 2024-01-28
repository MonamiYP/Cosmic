cmake_minimum_required(VERSION 3.0.0)

project(Space_Explorer)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(include/glfw)

target_include_directories(${PROJECT_NAME} 
    PUBLIC include/glfw/include
)

# target_link_directories(${PROJECT_NAME}
#     PRIVATE include/glfw/src
# )

target_link_libraries(${PROJECT_NAME} 
    glfw
)

# target_include_directories(${PROJECT_NAME} PRIVATE include
#     ${CMAKE_CURRENT_LIST_DIR}/include/glad)

# find_package(OpenGL REQUIRED)
# target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)