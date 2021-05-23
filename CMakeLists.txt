cmake_minimum_required(VERSION 3.1)

project(Playground VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/glfw")
add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/glad")
add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/assimp")
add_subdirectory("${PROJECT_SOURCE_DIR}/Engine")
add_subdirectory("${PROJECT_SOURCE_DIR}/Example1")
add_subdirectory("${PROJECT_SOURCE_DIR}/Example2")
add_subdirectory("${PROJECT_SOURCE_DIR}/Example3")
add_subdirectory("${PROJECT_SOURCE_DIR}/Example4")
