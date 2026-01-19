#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <vector>

constexpr float PI = 3.14159265358979323846f;

constexpr int SCREEN_WIDTH = 320;
constexpr int SCREEN_HEIGHT = 240;

constexpr int HUD_HEIGHT = 40;
constexpr int USABLE_SCREEN_HEIGHT = SCREEN_HEIGHT - HUD_HEIGHT;

constexpr int BLOCK_SIZE = 64;

// TODO: Find better way to set init pos
constexpr int INIT_POS_X = 96;
constexpr int INIT_POS_Y = 96;

// Field of View: 60°
constexpr float FOV = PI / 3;

// Projection Plane Distance
const float PPD = (SCREEN_WIDTH / 2.0f) / tan(FOV / 2.0f);

#endif
