cmake_minimum_required(VERSION 3.1)

project(Minecraft VERSION 0.1)

SET(CXX_STANDARD 14)
SET(CXX_STANDARD_REQUIRED true)

# Add all the filters
file(GLOB_RECURSE TERRAIN
    PRIVATE "${PROJECT_SOURCE_DIR}/terrain/*.hpp"
    PRIVATE "${PROJECT_SOURCE_DIR}/terrain/*.cpp"
)

file(GLOB_RECURSE SHADERS
    PRIVATE "${PROJECT_SOURCE_DIR}/shaders/*.vert"
    PRIVATE "${PROJECT_SOURCE_DIR}/shaders/*.frag"
)

add_executable(${PROJECT_NAME}
    ${TERRAIN}
    ${SHADERS}
    Source.cpp
)

source_group("terrain"              FILES ${TERRAIN})
source_group("shaders"              FILES ${SHADERS})


target_include_directories(${PROJECT_NAME}
    PRIVATE "${PROJECT_SOURCE_DIR}/../Engine" 
    PRIVATE "${PROJECT_SOURCE_DIR}/../vendor/glm" 
    PRIVATE "${PROJECT_SOURCE_DIR}/../vendor/glad/include" 
    PRIVATE "${PROJECT_SOURCE_DIR}/../vendor/stb_image"
)

target_link_libraries(${PROJECT_NAME} Engine)
