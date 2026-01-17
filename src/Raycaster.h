#ifndef __RAYCASTER__
#define __RAYCASTER__

#include "Constants.h"
#include "Map.h"
#include "Vector.h"

#include <iostream>
#include <limits>

class Raycaster {
  private:
    // Small offset to push ray intersections inside the correct grid cell
    // and avoid precision issues when hitting tile boundaries.
    static constexpr float EPSILON = 0.0001f;

    Vector horizontalRay;
    float hRayDist = std::numeric_limits<float>::infinity();

    Vector verticalRay;
    float vRayDist = std::numeric_limits<float>::infinity();

    Vector finalRay;
    float finalRayDist = std::numeric_limits<float>::infinity();

    Vector &playerPos;
    float playerAngle;
    float rayAngle;

    Map &map;

    void calculateVerticalRay();

    void calculateHorizontalRay();

    void calculateFinalRay();

  public:
    Raycaster(Vector &playerPos, float playerAngle, Map &map);

    void calculateRay(float rayAngle);

    float getDistance();

    void renderWalls(int pos);

    ~Raycaster() = default;
};

#endif
