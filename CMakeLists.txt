cmake_minimum_required(VERSION 3.11.3)
project(wlEngine VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/include)
set(SDL2_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/lib)

set(glm_LIBRAY ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glm/lib)
set(glm_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glm/include)

set(Box2D_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/Box2D/include)
set(Box2D_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/third_party/Box2D/lib)

set(json_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/json/include)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${glm_INCLUDE_DIR})
include_directories(${Box2D_INCLUDE_DIR})
include_directories(${json_INCLUDE_DIR})

link_directories(${glm_LIBRAY})
link_directories(${SDL2_LIBRARY})
link_directories(${Box2D_LIBRARY})

file(GLOB source_file
    "${CMAKE_CURRENT_SOURCE_DIR}/Math/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/GameObject/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Graphics/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Memory/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Event/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(wlEngine SHARED
    ${source_file}
)

TARGET_LINK_LIBRARIES(wlEngine glm_shared)
TARGET_LINK_LIBRARIES(wlEngine SDL2)
TARGET_LINK_LIBRARIES(wlEngine SDL2_image)
TARGET_LINK_LIBRARIES(wlEngine Box2D)


