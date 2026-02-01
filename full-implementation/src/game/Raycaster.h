#ifndef __RAYCASTER__
#define __RAYCASTER__

#include "../components/Player.h"
#include "../maps/Map.h"
#include "../utils/Constants.h"
#include "../utils/Vector.h"

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

    float rayAngle;

    Ray horizontalRay;
    Ray verticalRay;

    const Player &player;
    const Map &map;

    /**
     * Checks if the angle is facing up (angle between 180° and 360°)
     * @return true when angle is facing up, false otherwise
     */
    bool isAngleFacingUp() const;

    /**
     * Checks if the angle is facing left (angle between 90° and 270°)
     * @return true when angle is facing left, false otherwise
     */
    bool isAngleFacingLeft() const;

    /**
     * Check if a ray can be cast in the given direction, rays parallel to grid
     * lines would never intersect and cause division by zero or infinite loops
     * @param direction the direction of the ray
     * @return true if ray has a valid angle for intersection, false if parallel
     */
    bool isRayValid(RayDirection direction) const;

    /**
     * Calculates the initial position for the ray, this means the first
     * collision with the next block in the map
     * @param offset the offset that will be used in the calculation
     * @param tangent the tangent that will be used in the calculation
     * @param direction the direction of the ray
     * @return a Vector with the initial position of the ray
     */
    Vector calculateInitPos(float offset, float tangent,
                            RayDirection direction) const;

    /**
     * Given a ray and a Vector step, it will check if the ray collides with a
     * wall, in that case it will end, if not it will add step to the wall and
     * keep searching until finds a wall or goes outside the map
     * @param ray a Ray with the data of the ray
     * @param step the step to be added to the ray position until find a wall
     */
    void moveRayIntoWall(Ray &ray, const Vector &step);

    /**
     * Does all the calculation to find the ray that collidies with a wall, for
     * vertical and horizontal orientations
     * @param ray the information of the ray
     * @param rayConfig additional info of ray, like angle orientation and
     * tangent
     */
    void calculateRay(Ray &ray, RayConfig &rayConfig);

    /**
     * Generates the data needed for the ray that collidies with a wall in the
     * map vertically (verticalRay)
     */
    void calculateVerticalRay();

    /**
     * Generates the data needed for the ray that collidies with a wall in the
     * map horizontally (horizontalRay)
     */
    void calculateHorizontalRay();

    /**
     * Select the ray closest to the player and returns it
     * @return the ray that is closest to the player
     */
    const Ray &getClosestRay();

  public:
    Raycaster(const Player &player, const Map &map);

    /**
     * Returns the ray that is closest to the player
     * @param rayAngle the angle of the ray we want to calculate
     * @return a Ray with all the info of the ray
     */
    const Ray &getRay(float rayAngle);

    Raycaster(const Raycaster &copy) = delete;
    Raycaster operator=(const Raycaster &copy) = delete;

    ~Raycaster() = default;
};

#endif
