cmake_minimum_required(VERSION 3.1)

project(Engine VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Add all the cpp files
file(GLOB SOURCES 
    PRIVATE "${PROJECT_SOURCE_DIR}/*.cpp"
)

# add all the header files
file(GLOB HEADERS 
    PRIVATE "${PROJECT_SOURCE_DIR}/*.hpp"
)

file(GLOB_RECURSE CORE 
    PRIVATE "${PROJECT_SOURCE_DIR}/Core/*.hpp"
    PRIVATE "${PROJECT_SOURCE_DIR}/Core/*.cpp"
)

file(GLOB_RECURSE SHADERS 
    PRIVATE "${PROJECT_SOURCE_DIR}/Shaders/*.hpp"
    PRIVATE "${PROJECT_SOURCE_DIR}/Shaders/*.cpp"
)

file(GLOB_RECURSE TEXTURES 
    PRIVATE "${PROJECT_SOURCE_DIR}/Textures/*.hpp"
    PRIVATE "${PROJECT_SOURCE_DIR}/Textures/*.cpp"
)


file(GLOB_RECURSE RENDERER 
    PRIVATE "${PROJECT_SOURCE_DIR}/Renderer/*.hpp"
    PRIVATE "${PROJECT_SOURCE_DIR}/Renderer/*.cpp"
)


file(GLOB_RECURSE EVENTS 
    PRIVATE "${PROJECT_SOURCE_DIR}/Events/*.hpp"
    PRIVATE "${PROJECT_SOURCE_DIR}/Events/*.cpp"
)

add_library(${PROJECT_NAME} 
    ${SOURCES} 
    ${HEADERS} 
    ${CORE} 
    ${SHADERS}
    ${RENDERER}
    ${TEXTURES}
    ${EVENTS}
)

source_group("Core"                FILES ${CORE})
source_group("Shaders"             FILES ${SHADERS})
source_group("Textures"            FILES ${TEXTURES})
source_group("Renderer"            FILES ${RENDERER})
source_group("Events"              FILES ${EVENTS})

#Add Libraries
target_include_directories(${PROJECT_NAME} 
    PRIVATE "${PROJECT_SOURCE_DIR}/../vendor/glm" 
    PRIVATE "${PROJECT_SOURCE_DIR}/../vendor/glad/include"
    PRIVATE "${PROJECT_SOURCE_DIR}/../vendor/stb_image"
)

target_link_libraries(${PROJECT_NAME} glfw opengl32.lib glad assimp zlibstatic)