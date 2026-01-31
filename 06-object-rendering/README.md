# Step 6 - Object Rendering

![objects](https://github.com/user-attachments/assets/f25445c2-8048-40e0-8f3d-f908e270e78e)

In this step, we add sprites (objects) to the scene, this are going to be just objects on the screen, but we can also use this logic to show items like consumables or another players/enemies.

## Sprites vs Walls

**Walls** are part of the grid and detected through raycasting.

**Sprites** are free-standing objects placed at specific coordinates:
- Can be positioned anywhere (not limited to grid)
- Need to be sorted by distance for proper rendering
- Require transparency (alpha channel) to blend with the scene
- Scale with distance just like walls

## Understanding Camera Space

Before we do any complex calculations, we first check: **Is the object even visible to the player?**

If a sprite is behind you, or too far to your left or right (outside your 60° field of view), there's no point in rendering it. This optimization saves processing time - we only transform and render sprites the player can actually see.

Once we confirm the sprite is within the FOV, we can advance to calculating exactly where it should appear on screen.

We need to know:
- How far in front of (or behind) the camera is the sprite? **(depth)**
- How far left or right from center view is the sprite? **(horizontal offset)**

## Projecting onto the Screen

Once we know a sprite is visible, we need to figure out where it appears on our screen.

Think of your screen as a window you're looking through. The sprite exists somewhere in the 3D world, and we need to find which spot on that flat window corresponds to the sprite's position.

### Calculation horizontal position

First, we find the angle between where you're looking and where the sprite is. This tells us if the sprite is to your left, right, or straight ahead.

We use this angle along with something called the Projection Plane Distance (PPD) - think of it as our "zoom level" - to calculate exactly which horizontal pixel the sprite should appear at. Sprites directly ahead appear in the center of the screen, while sprites to the side appear toward the edges.

### Calculating Distance

Calculating the distance is easy as we have the position of the player and the position of the object we can just use our `Vector` function `distance()`

## Column-by-Column Rendering

When a sprite is close to the camera, it might span 100 screen columns but the texture is only 64 pixels wide. We need to "stretch" those 64 texture columns across 100 screen columns.

This means some texture columns get drawn multiple times:

If the sprite is **twice as wide on screen** as the texture, each texture column is drawn twice. If it's **half as wide**, we skip every other texture column. The calculation automatically maps screen position to the correct texture column.

## The Painter's Algorithm

When multiple sprites exist in the scene, we must draw them in the correct order: **farthest to nearest**.

Imagine painting a landscape - you paint the distant mountains first, then closer hills, then nearby trees. Each layer paints over what's behind it.

The rendering order is:

1. **Walls first** - Raycasting renders all walls and stores their distances
2. **Sprites second** - Sorted from farthest to nearest

We calculate the distance from the player to each sprite, sort them, and render from back to front. This ensures closer sprites naturally appear in front of farther ones.

### Column-by-column depth checking

Here's the critical part: as we render each sprite column-by-column, we check if there's a wall closer than the sprite at that specific screen column.

If a wall is closer, we skip the rendering of that column as we know that the wall is blocking it, otherwise we render the sprite column because the object is in front of the wall

This means a sprite can be partially hidden - some columns visible, others blocked by walls. This per-column depth test creates realistic occlusion, where sprites can peek around corners or be partially hidden behind walls.

By combining the painter's algorithm (sprite-to-sprite ordering) with column depth testing (sprite-to-wall ordering), we achieve proper depth rendering throughout the entire scene.
