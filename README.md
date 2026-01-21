# Raycaster

A C++ and SDL2 raycasting engine inspired by Wolfenstein 3D.

## Status

Under active development. 

Documentation and refactoring are in progress, and the tutorial is still in an early stage.

## Requirements

- C++11 compatible compiler
- SDL2
- SDL2_image
- CMake

### Install dependencies
``` bash
sudo dnf install gcc-c++ cmake SDL2-devel SDL2_image-devel
```

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
  <img width="583" height="126" alt="Formulas" src="https://github.com/user-attachments/assets/3f8251ef-4d0b-46ef-bb79-31f7b85ead2c" />
</p>

---

<p align=center>
  <img alt="Wolf3D" src="https://github.com/user-attachments/assets/40bb347a-0e80-429b-8eb2-fd5e3be9f9f0" />
</p>

