# Step 5 - Textured Walls

In this step, we will replace the solid color walls with textures, mimicking the classic Wolfenstein 3D rendering style.
By mapping texture columns onto each raycasted wall slice, we give depth and visual detail to the scene.

![textured_walls](https://github.com/user-attachments/assets/587b59ba-37d5-4833-bbf0-4b610463958d)

## From Solid Colors to Textures

Previously, we drew walls as solid colored vertical lines. Now each wall slice displays a thin vertical column from a texture:

### Texture Coordinate Calculation

For each ray that hits a wall, we need to determine two things:

#### 1. Which texture to use

The texture to use will be in base to the map, the map has the values 0 for nothing and other number for the walls, every number represents different sprites for the wall, so we are going to check what type of wall we are going to use and then set that one for our wallSprites.

``` cpp
int wallType = this->map.getBlock(ray.position) - 1;
this->wallSprites.setSprite(wallType);
```

#### 2. Which column of that texture to use

Based on where exactly the ray hit the wall

<img width="602" height="600" alt="rayWall" src="https://github.com/user-attachments/assets/a2bbad02-39bc-4a65-98c7-b2993cd353e0" />

In this example the ray hits a wall horizontally, we use the X coordinate of the hit position to determine which texture column to display, we use the modulo operator against `BLOCK_SIZE`:

```cpp
int textureColumn = int(ray.position.getX()) % BLOCK_SIZE;
```

This works because each texture has a width of `BLOCK_SIZE` pixels, so the modulo gives us the exact column within the texture (0 to BLOCK_SIZE-1).

## Wall Texture Variants

Remember our wall sprite sheet has light and dark variants for shading:

We are going to select the appropriate variant based on wall orientation

``` cpp
if (ray.direction == RayDirection::VERTICAL) {
  this->wallSprites.nextSprite();
}
```
When the direction is vertical we are going to use the variant, the variant is the next sprite on the sprite sheet of walls, so we are going to use the function `nextSprite()`
