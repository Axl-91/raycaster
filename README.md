# Raycaster

A C++ and SDL2 raycasting engine inspired by Wolfenstein 3D.

## Status

Under active development. 

Documentation and refactorings are in progress...

## Requirements

- C++11 compatible compiler
- SDL2
- SDL2_image
- CMake

### Install dependencies
``` bash
sudo dnf install gcc-c++ cmake SDL2-devel SDL2_image-devel
```

## Tutorial Path

### Steps

1. **[Player Movement](https://github.com/Axl-91/raycaster/tree/main/01-player-movement)**: Initialize SDL project, create the player class, and implement basic movement and rotation controls
2. **[Map Implementation](https://github.com/Axl-91/raycaster/tree/main/02-map-implementation)**: Create a 2D map system and implement collision detection to prevent walking through walls
3. **[Basic Raycasting](https://github.com/Axl-91/raycaster/tree/main/03-basic-raycasting)**: Implement the raycasting algorithm - casting rays across the field of view to detect walls
4. **[Raycasting Walls](https://github.com/Axl-91/raycaster/tree/main/04-raycasting-walls)**: Transform ray distances into 3D wall rendering, apply fisheye correction, and add directional shading for depth
5. **[Textured Walls](https://github.com/Axl-91/raycaster/tree/main/05-textured-walls)**: Replace flat-colored walls with textures, implement texture sampling per ray, and align textures correctly on vertical and horizontal hits.
6. **[Rendering Objects](https://github.com/Axl-91/raycaster/tree/main/06-rendering-objects)**: Render sprites (objects) in the world, handle perspective scaling, visibility checks, and correct occlusion against walls.

### Complete Implementation

**[Full Implementation](https://github.com/Axl-91/raycaster/tree/main/full-implementation)**: Fully-featured raycaster with HUD, weapons, and shooting mechanics. Use as reference or starting point for your own game.

## Build and Run
``` bash
# BUILD 
cmake -S . -B build
cd build
make

# RUN
./main
```

### For a Debug build
``` bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

## About

This is a recreational, step-by-step raycasting project.

The goal of this project is to **learn and understand raycasting by building it gradually**, experimenting with the math, and visualizing how each part of the algorithm works. 

**What is Raycasting?**

Raycasting is a rendering technique that simulates 3D perspective by:
1. Casting rays from the player's position
2. Detecting wall intersections
3. Drawing vertical slices based on distance
4. Creating the illusion of 3D depth

## Raycasting Bible
<p align=center>
  <img width="300" alt="Triangle" src="https://github.com/user-attachments/assets/0feba2ee-cb2f-4f4f-8f3d-fef958d64d6b" />
</p>
<p align=center>
  <img width="529" height="209" alt="Formulas" src="https://github.com/user-attachments/assets/c72b3d01-18a0-40d4-9523-a01a7720da44" />
</p>

---

<p align=center>
  <img alt="Wolf3D" src="https://github.com/user-attachments/assets/40bb347a-0e80-429b-8eb2-fd5e3be9f9f0" />
</p>

