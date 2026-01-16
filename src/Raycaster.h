#ifndef __RAYCASTER__
#define __RAYCASTER__

#include "Map.h"
#include "Vector.h"
#include "constants.h"
#include <iostream>
#include <limits>

class Raycaster {
  private:
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

    void render(int pos);

    ~Raycaster() = default;
};

#endif
