cmake_minimum_required(VERSION 3.11.3)
project(wlEngine VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DRELEASE")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/Box2D/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/assimp/assimp-4.0.1)

set(SDL2_INCLUDE_DIR third_party/SDL2/include)
set(glm_INCLUDE_DIR third_party/glm/) #header only
set(json_INCLUDE_DIR third_party/json/include) #header only
set(stb_image_INCLUDE_DIR third_party/stb/include) #header only
set(glad_INCLUDE_DIR third_party/glad/include)
set(assimp_INCLUDE_DIR third_party/assimp/include)
set(dirent_INCLUDE_DIR third_party/dirent/include)

#set(CMAKE_CXX_FLAGS -Wno-deprecated)
find_package(OpenGL REQUIRED)
#find_library(glm_LIBRARY glm HINTS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glm/lib/windows)
#find_library(SDL2_LIBRARY SDL2 HINTS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/lib/windows)
#find_library(SDL2_image_LIBRARY SDL2_image HINTS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/lib/windows)
find_library(assimp_LIBRARY assimp HINTS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/assimp/lib/windows)

SET(SDL2_LIBRARY_DIRECTORIES
  debug ${SDL2_LIBRARY_DEBUG}
  optimized ${SDL2_LIBRARY_RELEASE}
)

include_directories(
    ${glm_INCLUDE_DIR}
    ${json_INCLUDE_DIR}
    ${stb_image_INCLUDE_DIR}
    ${glad_INCLUDE_DIR}
    ${assimp_INCLUDE_DIR} 
    ${dirent_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR}
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
    #"${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/src/glad.cpp"
)

add_library(wlEngine STATIC
    ${source_file}
)

TARGET_LINK_LIBRARIES(wlEngine
    Box2D
    glad
    SDL2-static
    ${OPENGL_LIBRARIES}
    ${assimp_LIBRARY}
)

TARGET_INCLUDE_DIRECTORIES(wlEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${glm_INCLUDE_DIR}
    ${json_INCLUDE_DIR}
    ${stb_image_INCLUDE_DIR}
    ${glad_INCLUDE_DIR}
    ${assimp_INCLUDE_DIR} 
    ${dirent_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR}
)