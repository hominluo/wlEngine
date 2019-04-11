cmake_minimum_required(VERSION 3.11.3)

project(wlEngine VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/include)
set(glm_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glm/include)
set(Box2D_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/Box2D/include)
set(json_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/json/include)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${glm_INCLUDE_DIR})
include_directories(${Box2D_INCLUDE_DIR})
include_directories(${json_INCLUDE_DIR})

#set(CMAKE_CXX_FLAGS -Wno-deprecated)
find_package(OpenGL)
find_library(glm_LIBRARY glm HINTS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glm/lib/windows)
find_library(SDL2_LIBRARY SDL2 HINTS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/lib/windows)
find_library(Box2D_LIBRARY Box2D HINTS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/Box2D/lib/windows)
find_library(SDL2_image_LIBRARY SDL2_image HINTS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/lib/windows)

file(GLOB source_file
    "${CMAKE_CURRENT_SOURCE_DIR}/Math/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/GameObject/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Graphics/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Memory/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Event/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Physics/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(wlEngine STATIC
    ${source_file}
)

TARGET_LINK_LIBRARIES(wlEngine 
    ${glm_LIBRARY}
    ${SDL2_LIBRARY}
    ${Box2D_LIBRARY}
    ${SDL2_image_LIBRARY}
    ${OPENGL_gl_LIBRARY}
)
