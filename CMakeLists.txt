cmake_minimum_required(VERSION 3.11.3)

project(wlEngine VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/include)
set(glm_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glm/include)
set(Box2D_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/Box2D/include)
set(json_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/json/include)
set(stb_image_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/stb/include)
set(glad_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include)
set(assimp_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/assimp/include)
set(dirent_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/dirent/include)

#set(CMAKE_CXX_FLAGS -Wno-deprecated)
find_package(OpenGL REQUIRED)
find_library(glm_LIBRARY glm HINTS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glm/lib/windows)
find_library(SDL2_LIBRARY SDL2 HINTS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/lib/windows)
find_library(Box2D_LIBRARY Box2D HINTS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/Box2D/lib/windows)
find_library(SDL2_image_LIBRARY SDL2_image HINTS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/lib/windows)
find_library(assimp_LIBRARY assimp HINTS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/assimp/lib/windows)

include_directories(
    ${SDL2_INCLUDE_DIR}
    ${glm_INCLUDE_DIR}
    ${Box2D_INCLUDE_DIR}
    ${json_INCLUDE_DIR}
    ${stb_image_INCLUDE_DIR}
    ${glad_INCLUDE_DIR}
    ${assimp_INCLUDE_DIR} 
    ${dirent_INCLUDE_DIR} 
)

file(GLOB source_file
    "${CMAKE_CURRENT_SOURCE_DIR}/Math/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Math/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/GameObject/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/GameObject/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Component/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Component*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Component/Struct/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Component/Struct/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/System/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/System/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Graphics/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Graphics/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Memory/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Memory/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Event/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Event/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Physics/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Physics/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/GameEditor/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/GameEditor/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Manager/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Manager/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Utility/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Utility/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/src/glad.cpp"
)

add_library(wlEngine STATIC
    ${source_file}
)

TARGET_LINK_LIBRARIES(wlEngine
    ${glm_LIBRARY}
    ${SDL2_LIBRARY}
    ${Box2D_LIBRARY}
    ${SDL2_image_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${assimp_LIBRARY}
)
