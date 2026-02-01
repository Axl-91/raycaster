#ifndef __PLAYER__
#define __PLAYER__

#include "../maps/Map.h"
#include "../utils/Constants.h"
#include "../utils/Vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Player {
  private:
    static constexpr float PLAYER_RADIUS = 6.0f;
    static constexpr float MOVE_SPEED = 3.0f;
    static constexpr float ROTATION_SPEED = PI / 36;

    float posX;
    float posY;
    float angle = 0;
    Map &map;

    /**
     * Player movement controls.
     * Updates position or orientation angle based on input.
     */
    void moveForward();
    void moveBackward();
    void rotateLeft();
    void rotateRight();

    /**
     * Checks if the player can move to the x,y position
     * @param x the X position to validate
     * @param y the Y position to validate
     * @return true if the position is valid, false otherwise
     */
    bool canMove(float x, float y) const;

  public:
    Player(Map &map);

    /**
     * @return Position of the player
     */
    Vector getPos() const { return Vector(posX, posY); };

    /**
     * @return Angle of the player
     */
    float getAngle() const { return angle; };

    /**
     * Handles the movements of the player based on keyboard input
     */
    void handleMovement();

    /**
     * Checks if the object is visible by the Player
     * @param posObj a Vector that represents the position of the object
     */
    bool objIsVisible(const Vector &posObj) const;

    void render(SDL_Renderer *renderer) const;

    Player(const Player &copy) = delete;
    Player operator=(const Player &copy) = delete;

    ~Player();
};

#endif
