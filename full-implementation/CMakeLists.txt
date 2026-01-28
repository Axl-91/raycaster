cmake_minimum_required(VERSION 3.10)

project(Raycaster LANGUAGES CXX)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(SOURCES
    src/Game.cpp
    src/Vector.cpp
    src/Hud.cpp
    src/Guns.cpp
    src/Player.cpp
    src/Raycaster.cpp
    src/Map.cpp
    src/Sprites.cpp
    src/Renderer.cpp
    src/DefaultMapData.cpp
    src/DefaultObjects.cpp
)

add_library(sdl-lib)
target_sources(sdl-lib PRIVATE ${SOURCES})

target_compile_features(sdl-lib PRIVATE cxx_std_11)

target_compile_options(sdl-lib PRIVATE
    $<$<CONFIG:Debug>:-g -O0 -Wall -Wextra>
)

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE sdl-lib SDL2 SDL2_image)

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
