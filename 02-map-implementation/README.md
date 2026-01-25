# Step 2 – Map Implementation

In this step we introduce the **map system**, which defines the world layout used by the raycasting engine.

The map is implemented as a **15×20 grid**, chosen to roughly match the screen resolution of **320×240**. This makes it easy to later represent the map on screen without scaling issues.

![map](https://github.com/user-attachments/assets/c5991d74-e3f9-4a35-9633-a0de64db7147)

## Map Layout

- The map is stored as a 2D grid of integers.
- Each cell represents a tile in the world.
- Tile values:
  - `0` → empty space
  - `!= 0` → wall

## Collision Detection

Basic collision detection is implemented so that:

- The player **cannot move outside the map**
- The player **cannot walk through walls**

Before updating the player position, the map is queried to check whether the target position is valid. If the position corresponds to a wall, the movement is blocked.

As our map is surrounded by walls is impossible for the player to move outside the map. 

## Map Rendering

The map will be rendered in a **top-down view**:

- Walls are rendered in gray
- Empty spaces are rendered in black
