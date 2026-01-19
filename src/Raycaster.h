#ifndef __RAYCASTER__
#define __RAYCASTER__

#include "Constants.h"
#include "Map.h"
#include "Player.h"
#include "Vector.h"

#include <iostream>
#include <limits>

enum class RayDirection { HORIZONTAL, VERTICAL };

typedef struct Ray {
    Vector position;
    float distance = std::numeric_limits<float>::infinity();
    RayDirection direction;
} Ray;

typedef struct RayConfig {
    bool isNegativeDir;
    float tangent;
} RayConfig;

class Raycaster {
  private:
    /*
      Small offset to push ray intersections inside the correct grid cell
      and avoid precision issues when hitting tile boundaries.
    */
    static constexpr float EPSILON = 0.0001f;

    Ray horizontalRay;
    Ray verticalRay;
    Ray finalRay;

    Vector playerPos;
    float playerAngle;
    float rayAngle;

    Map &map;

    bool isAngleFacingUp();

    bool isAngleFacingLeft();

    bool isRayValid(RayDirection direction);

    Vector calculateInitPos(float blockPos, float offset, float tangent,
                            RayDirection direction);

    void moveRayIntoWall(Ray &ray, const Vector &step);

    void calculateVerticalRay();

    void calculateHorizontalRay();

    void calculateFinalRay();

    void calculateRay(Ray &ray, RayConfig &rayConfig);

  public:
    Raycaster(const Player &player, Map &map);

    void updatePlayerValues(const Player &player);

    Ray &getRay(float rayAngle);

    ~Raycaster() = default;
};

#endif
