# Step 3 - Basic Raycasting

In this step, we implement the core raycasting algorithm that creates a 3D perspective from a 2D map. We'll cast rays from the player's position to detect walls and calculate distances.

![raycasting](https://github.com/user-attachments/assets/500855fa-a3cf-4bde-a6e6-e9f0ad0f4f59)

---

## The Raycasting Concept

Raycasting simulates 3D by casting rays from the player's position in different directions. Each ray:

1. Travels outward from the player at a specific angle
2. Checks for intersections with map walls
3. Stops when it hits a wall
4. Records the distance traveled

By casting many rays across the player's field of view, we can build a 3D scene where:
- **Close walls** appear tall (short distance)
- **Far walls** appear short (long distance)

## Field of View (FOV)

We use a **60-degree field of view** (π/3 radians):
```cpp
static constexpr float FOV = PI / 3;  // 60 degrees total
static constexpr float OFFSET_RAYCASTER = FOV / 2;  // Start at -30°
static constexpr float STEP_RAYCASTER = FOV / SCREEN_WIDTH;
```

**Why 60 degrees?**
- Matches human peripheral vision when focused
- Provides good sense of depth without distortion
- Classic FPS standard (Wolfenstein 3D, DOOM)

<img width="497" height="497" alt="FOV" src="https://github.com/user-attachments/assets/de948fbd-9dd9-4905-ae0b-b17f974bf906" />
<br/>
<em>Image taken from <a href="https://splashkit.io/guides/physics/8-3d-projection-raycasting/">SplashKit</a></em>

## One Ray Per Screen Column

We cast **exactly 320 rays** to fill the 320-pixel-wide screen:
```
Player facing angle: 45° (for example)

Ray angles:
Ray 0:   45° - 30° = 15°  → draws at screen X = 0
Ray 1:   15° + step       → draws at screen X = 1
Ray 2:   15° + step       → draws at screen X = 2
...
Ray 319: 45° + 30° = 75°  → draws at screen X = 319

Total coverage: 60° field of view
```

## Ray Casting Algorithm

For each ray, we need to find where it intersects with the grid:

### 1. Horizontal Intersections

Check where the ray crosses horizontal grid lines:

- Calculate first horizontal intersection
- Step along horizontal grid lines
- Stop when hitting a wall

<img width="640" height="480" alt="horizontals" src="https://github.com/user-attachments/assets/eb81c174-572b-4161-afd9-d64dca0cb402" />

<img width="700" height="400" alt="hRay" src="https://github.com/user-attachments/assets/a5fc9935-f919-46ed-922b-4583c464b262" />

<em>Remember the [Raycasting Bible](https://github.com/Axl-91/raycaster?tab=readme-ov-file#raycasting-bible)</em>

### 2. Vertical Intersections

Check where the ray crosses vertical grid lines:

- Calculate first vertical intersection
- Step along vertical grid lines
- Stop when hitting a wall

<img width="640" height="480" alt="verticals" src="https://github.com/user-attachments/assets/76ee4c09-5538-4910-809a-47e032860f5b" />


### 3. Choose Final Ray

After calculating both horizontal and vertical ray intersections, we choose whichever is closest to the player. The closest ray is the one we project onto the screen.

## Visualization

In this step, we render a top-down view showing:

- **Red square**: Player position
- **Yellow line**: Player's viewing direction
- **Green lines**: All 320 rays spreading across the FOV

This helps visualize:
- How rays spread across the field of view
- Which walls each ray hits
- The 60-degree cone of vision
