# Step 4 - Raycasting Walls

In this step, we transform the top-down view into a proper first-person 3D perspective by rendering walls based on ray distances.

![walls](https://github.com/user-attachments/assets/1acdd86c-703b-4460-8bfa-89013f39da77)

## From Rays to Walls

Instead of drawing rays in top-down view, we now:

- **Cast rays across the field of view** (see Step 03)

- **Calculate wall height based on ray distance**  
  Uses the formula: `wallHeight = (BLOCK_SIZE * BLOCK_SIZE / distance)`
  
  Closer walls have shorter distances, resulting in larger heights on screen. This inverse relationship creates the depth illusion - just like how nearby objects look bigger than distant ones in real life.

- **Render walls one vertical pixel column at a time**  
  We draw 320 vertical lines (one per ray/screen column), each with height determined by that ray's distance. This slice-by-slice approach builds the complete 3D view:
```
  Ray 0 → Wall height 100px → Draw line at X=0, 100px tall
  Ray 1 → Wall height 98px  → Draw line at X=1, 98px tall
  ...
  Ray 319 → Wall height 50px → Draw line at X=319, 50px tall
```

**Apply shading to distinguish wall orientations**  
  
  We use different brightness levels for vertical vs horizontal walls to add depth and help distinguish wall orientations:
  
  - **Horizontal walls** (North/South facing): Brighter
  - **Vertical walls** (East/West facing): Darker

```cpp
  bool isDark = ray.direction == RayDirection::VERTICAL;
```
  
  This fixed lighting scheme creates visual distinction between wall types without complex calculations. It's a classic technique from Wolfenstein 3D that helps players navigate 3D spaces by making different wall orientations instantly recognizable.

## Fisheye

In a raycasting engine, walls that are directly in front of the player should appear taller than walls that are farther away. However, when rays are cast at different angles, walls near the edges of the screen appear stretched and curved. This distortion is known as the **fisheye effect**.

The fisheye effect happens because the raw distance of each ray is measured along the ray itself, not straight ahead from the player. Rays cast at sharper angles travel a longer distance to hit the same wall, even though the wall is actually at the same depth.

### Fixing the Fisheye Effect

To fix this distortion, we need the perpendicular distance from the player to the wall, not the ray’s full length.

We achieve this by projecting the ray distance onto the player’s viewing direction. This is done by multiplying the ray distance by the cosine of the angle difference between the ray and the player’s view angle:

<img width="683" height="409" alt="Fisheye" src="https://github.com/user-attachments/assets/c0f1f5ab-3f82-4756-bfb4-858e2a6ff042" />

<em>Remember the [Raycasting Bible](https://github.com/Axl-91/raycaster?tab=readme-ov-file#raycasting-bible)</em>

By using this corrected distance, all walls at the same depth are rendered with the same height, producing a visually correct and distortion-free result.
