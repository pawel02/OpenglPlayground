cmake_minimum_required(VERSION 3.1)

project(Example6 VERSION 1.0)

SET(CXX_STANDARD 14)
SET(CXX_STANDARD_REQUIRED true)

add_executable(${PROJECT_NAME} Source.cpp)

target_include_directories(${PROJECT_NAME}
    PRIVATE "${PROJECT_SOURCE_DIR}/../Engine" 
    PRIVATE "${PROJECT_SOURCE_DIR}/../vendor/glm" 
    PRIVATE "${PROJECT_SOURCE_DIR}/../vendor/glad/include" 
    PRIVATE "${PROJECT_SOURCE_DIR}/../vendor/stb_image"
)

target_link_libraries(${PROJECT_NAME} Engine)
