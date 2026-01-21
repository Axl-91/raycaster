# Step 01 - Player Movement

In this first step, we'll create a basic player that can move around a 2D space and rotate. This establishes the foundation for our raycaster.

## SDL Setup

### Understanding the Coordinate System

SDL uses an inverted Y-axis:
- Y = 0 is at the **top** of the screen
- Y increases **downward**

<img width="540" height="460" alt="sdl_coords" src="https://github.com/user-attachments/assets/6b88bf43-9e7c-4351-acd6-b6355022bf9f" />

### Delay (FPS)

We'll use `SDL_Delay(16)` to cap the movement to an aprox. 60FPS

### Screen Resolution

Our window will be **640x480** (this can be changed in code) but our logical resolution is going to be **320x240**. This is to **mimic the way old games would look like** - with visible, chunky pixels that give that authentic retro aesthetic.

https://github.com/Axl-91/raycaster/blob/e61ed69b4ff57ac169c7f3453b49be92148d13ec/01-player-movement/src/Game.cpp#L18-L31

## Renderer

The Renderer class is going to be the sole responsable of rendering everything on the program, as for now it will only render the player

## Player

The `Player` class contains:

- **Position** (`posX`, `posY`): Player's location in the world (in pixels)
- **Angle**: Direction the player is facing (in radians)
- **Movement speed**: How fast the player moves

### Controls

- **W / Up Arrow**: Move forward
- **S / Down Arrow**: Move backward
- **A / Left Arrow**: Rotate left
- **D / Right Arrow**: Rotate right
- **ESC**: Exit

### Movement System

We use `SDL_GetKeyboardState()` instead of event-based input to allow smooth, simultaneous key presses (e.g., moving forward while rotating).
https://github.com/Axl-91/raycaster/blob/e61ed69b4ff57ac169c7f3453b49be92148d13ec/01-player-movement/src/Player.cpp#L33-L48

### Rendering

We render a simple top-down view to visualize the player's position and orientation.

### What We Render

1. **Player position**: A small red square
2. **View direction**: A yellow line showing where the player is facing
