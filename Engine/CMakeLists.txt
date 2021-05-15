cmake_minimum_required(VERSION 3.1)

project(Engine VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_library(${PROJECT_NAME} Engine.cpp)

#Add Libraries
target_include_directories(${PROJECT_NAME} 
    PRIVATE "${PROJECT_SOURCE_DIR}/../vendor/glm" 
    PRIVATE "${PROJECT_SOURCE_DIR}/../vendor/glad/include" 
    PRIVATE "${PROJECT_SOURCE_DIR}/../vendor/stb_image"
    PRIVATE "${PROJECT_SOURCE_DIR}/../vendor/assimp/include"
    PRIVATE "${PROJECT_BINARY_DIR}/../vendor/assimp/include"
    PRIVATE "${PROJECT_SOURCE_DIR}/../Engine"
)

target_link_directories(${PROJECT_NAME} 
    PRIVATE "${PROJECT_BINARY_DIR}/../vendor/assimp/contrib/zlib/Debug"
    PRIVATE "${PROJECT_BINARY_DIR}/../vendor/assimp/lib/Debug"
)

target_link_libraries(${PROJECT_NAME} glfw opengl32.lib glad)