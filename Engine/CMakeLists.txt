cmake_minimum_required(VERSION 3.1)

project(Engine VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Add all the cpp files
file(GLOB SOURCES 
    PRIVATE "${PROJECT_SOURCE_DIR}/Shaders/*.cpp"
    PRIVATE "${PROJECT_SOURCE_DIR}/Core/*.cpp"
    PRIVATE "${PROJECT_SOURCE_DIR}/*.cpp"
)

# add all the header files
file(GLOB HEADERS 
    PRIVATE "${PROJECT_SOURCE_DIR}/Shaders/*.hpp"
    PRIVATE "${PROJECT_SOURCE_DIR}/Core/*.hpp"
    PRIVATE "${PROJECT_SOURCE_DIR}/*.hpp"
)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

#Add Libraries
target_include_directories(${PROJECT_NAME} 
    PRIVATE "${PROJECT_SOURCE_DIR}/../vendor/glm" 
    PRIVATE "${PROJECT_SOURCE_DIR}/../vendor/glad/include"
    PRIVATE "${PROJECT_SOURCE_DIR}/../vendor/stb_image"
)

target_link_libraries(${PROJECT_NAME} glfw opengl32.lib glad assimp zlibstatic)