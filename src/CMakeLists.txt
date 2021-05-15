cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(${PROJECT_NAME} Source.cpp)

#Add GLFW
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/vendor/glm" "${PROJECT_SOURCE_DIR}/vendor/glad/include" "${PROJECT_SOURCE_DIR}/vendor/stb_image")

target_link_libraries(${PROJECT_NAME} glfw opengl32.lib glad)