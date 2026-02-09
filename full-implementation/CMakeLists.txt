cmake_minimum_required(VERSION 3.10)

project(Raycaster LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(yaml-cpp REQUIRED)

set(SOURCES
    src/game/Game.cpp
    src/game/Raycaster.cpp
    src/game/Renderer.cpp
    src/game/Config.cpp
    src/components/Player.cpp
    src/components/Sprite.cpp
    src/components/StaticSprite.cpp
    src/components/GunSprite.cpp
    src/components/HudSprite.cpp
    src/maps/Map.cpp
    src/maps/MapParser.cpp
    src/utils/Vector.cpp
)

# Create a library for SDL-related files
add_library(sdl-lib)
target_sources(sdl-lib PRIVATE ${SOURCES})

# Set C++ standard
target_compile_features(sdl-lib PRIVATE cxx_std_11)

# Set compile options for Debug configuration
target_compile_options(sdl-lib PRIVATE
    $<$<CONFIG:Debug>:-g -O0 -Wall -Wextra>
)

# Create the executable
add_executable(main src/main.cpp)

# Link libraries
target_link_libraries(main PRIVATE sdl-lib SDL2 SDL2_image yaml-cpp)

# Copy assets and resources to the build directory
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
