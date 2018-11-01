cmake_minimum_required (VERSION 3.1)
project(cayvrpg)

# Detect compiler
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(USING_GCC TRUE)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(USING_CLANG TRUE)
endif()

# For GCC and Clang, enable C++14
if(USING_GCC OR USING_CLANG OR OSX)
  add_compile_options(-std=c++14)
  if(SANITIZE)
    add_compile_options(-fsanitize=${SANITIZE})
    set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=${SANITIZE}")
  endif()
endif()

if(USING_GCC OR USING_CLANG OR OSX)
    add_compile_options(-pedantic -Wall -Wextra -Wmissing-declarations
                        -Wnon-virtual-dtor)
endif()

if(OSX)
    message(STATUS "OSX building enabled.")

    set(SDLIMAGE_LIBRARY /Library/Frameworks/SDL2_image.framework)
    set(SDLIMAGE_INCLUDE_DIR /Library/Frameworks/SDL2_image.framework/Headers)

    set(SDLMIXER_LIBRARY /Library/Frameworks/SDL2_mixer.framework)
    set(SDLMIXER_INCLUDE_DIR /Library/Frameworks/SDL2_mixer.framework/Headers)
endif()


set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
find_package(SDL2_mixer REQUIRED)
include_directories(${SDLMIXER_INCLUDE_DIR})
find_package(SDL2_image REQUIRED)
include_directories(${SDLIMAGE_INCLUDE_DIR})

# Vendored extlibs
include_directories(extlib/fmt)
add_library(fmt STATIC extlib/fmt/format.cc)

# We wanna include "kek.hpp" instead of "../../../kek.hpp" when we're in the deep
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(cayv src/main.cpp src/window.cpp src/game.cpp
                    src/scene.cpp src/init.cpp src/scenes/autismofields.cpp)

target_link_libraries(cayv ${SDL2_LIBRARY} ${SDLMIXER_LIBRARY} ${SDLIMAGE_LIBRARY} fmt)
