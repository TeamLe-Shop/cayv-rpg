cmake_minimum_required (VERSION 3.1)
project(cayvrpg)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(cayv src/main.cpp)

target_link_libraries(cayv ${SDL2_LIBRARY})
