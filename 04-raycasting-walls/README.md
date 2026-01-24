# Step 4 - Raycasting Walls

![walls](https://github.com/user-attachments/assets/1acdd86c-703b-4460-8bfa-89013f39da77)

In this step, we transform the top-down view into a proper first-person 3D perspective by rendering walls based on ray distances.

## From Rays to Walls

Instead of drawing rays in top-down view, we now:

- Cast rays across the field of view
- Calculate wall height based on ray distance (closer walls appear taller)
- Render walls one vertical pixel column at a time
- Apply shading to distinguish wall orientations and simulate directional lighting
