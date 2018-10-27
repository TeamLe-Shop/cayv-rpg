cmake_minimum_required (VERSION 3.1)
project(cayvrpg)

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

add_executable(cayv src/main.cpp)

target_link_libraries(cayv ${SDL2_LIBRARY} ${SDLMIXER_LIBRARY})
