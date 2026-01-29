# Step 6 - Object Rendering

![objects](https://github.com/user-attachments/assets/f25445c2-8048-40e0-8f3d-f908e270e78e)

In this step, we add sprites (objects) to the scene - enemies, items, decorations, or any non-wall elements that exist in the 3D world.

## Sprites vs Walls

**Walls** are part of the grid and detected through raycasting.

**Sprites** are free-standing objects placed at specific coordinates:
- Can be positioned anywhere (not limited to grid)
- Need to be sorted by distance for proper rendering
- Require transparency (alpha channel) to blend with the scene
- Scale with distance just like walls
