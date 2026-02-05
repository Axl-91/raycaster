# Complete Raycaster Implementation

This is the full-featured raycaster with all enhancements implemented. It demonstrates a complete, playable Wolfenstein 3D-style engine with HUD, weapons, and interactive elements.

![game](https://github.com/user-attachments/assets/125864cf-8960-478c-9de5-e9ca824ef51d)

## What's Included

Beyond the step-by-step tutorial, this implementation adds:

### HUD
- Health indicator (Incomplete)
- Ammo counter  (Incomplete)
- Selected weapon display
- Face/status indicator (Incomplete)

### Weapon System
- Multiple selectable weapons (keys 1-4)
- Shooting animations with sprite-based gun graphics
- Weapon display synchronized with HUD

## Screen Layout

The main 3D viewport will be different as we render the height at `SCREEN_HEIGHT - HUD_HEIGHT` to leave room for the HUD overlay.

```cpp
constexpr int SCREEN_HEIGHT = 240;
constexpr int HUD_HEIGHT = 40;

constexpr int USABLE_SCREEN_HEIGHT = SCREEN_HEIGHT - HUD_HEIGHT;
```

Walls & sprites rendering calculates positions within the reduced viewport, then the HUD is drawn on top.

### Weapon

#### Positioning

Weapons will be rendered at the center of the X-axis and at the bottom of the Y-axis.
  
#### Selection

Each weapon (1-4) corresponds to a different sprite in the gun sprite sheet. Selecting a weapon:
- Updates the gun sprite displayed at bottom-center
- Updates the weapon icon in the HUD
  
#### Animation

When firing:
1. `Space` key triggers `gun.handleShooting()`
2. Gun sprite cycles through animation frames
3. After animation completes, gun returns to idle state

## Extending This Implementation

This complete version serves as a foundation for your own enhancements. Consider adding:

- **Enemies** - Moving sprites that track the player
- **Doors** - Interactive wall segments that open/close
- **Sound effects** - Footsteps, gunshots, ambient audio
- **Multiple levels** - Map switching and progression
- **Pickups** - Health, ammo, and powerups

## From Tutorial to Your Own Game

The step-by-step tutorial teaches the fundamentals, this complete implementation shows how those pieces work together in a cohesive game.

**To learn from this code:**
1. Review how `Renderer` orchestrates all rendering subsystems
2. Study how `Game` manages the update loop and component interaction
3. Examine the separation between game logic and rendering
4. See how the HUD and viewport share screen space efficiently

The raycasting foundation is complete - now make it your own!

## Credits

Inspired by Wolfenstein 3D (id Software, 1992) and the classic raycasting techniques developed by John Carmack.

