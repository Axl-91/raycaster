#ifndef __RAYCASTER__
#define __RAYCASTER__

#include "Constants.h"
#include "Map.h"
#include "Player.h"
#include "Vector.h"

#include <iostream>
#include <limits>

typedef struct Ray {
    Vector position;
    float distance = std::numeric_limits<float>::infinity();
} Ray;

class Raycaster {
  private:
    /*
      Small offset to push ray intersections inside the correct grid cell
      and avoid precision issues when hitting tile boundaries.
    */
    static constexpr float EPSILON = 0.0001f;
    static constexpr int COL_WIDTH = 1;
    enum class RayDirection { HORIZONTAL, VERTICAL };

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

    Vector calculateInitialRay(float blockPos, float offset, float tang,
                               RayDirection direction);

    void moveRayIntoWall(Ray &ray, const Vector &step);

    void calculateVerticalRay();

    void calculateHorizontalRay();

    void calculateFinalRay();

  public:
    Raycaster(const Player &player, Map &map);

    void calculateRay(float rayAngle);

    float getDistance();

    void renderWalls(int posX);

    ~Raycaster() = default;
};

#endif
