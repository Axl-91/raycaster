#ifndef __MAP__
#define __MAP__

#include "Vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

typedef struct mapObject {
    Vector position;
    int type;
} MapObject;

class Map {
  private:
    int rows = -1;
    int columns = -1;

    std::vector<std::vector<int>> gridMap;
    std::vector<mapObject> vectObj;

    /**
     * Check if the x and y positions are inside the map array
     * @params x the X value in the array
     * @params y the Y value in the array
     */
    bool isInsideMap(float x, float y);

    /**
     * Gets the block in the position x and y
     * @params x the X value in the array
     * @params y the Y value in the array
     */
    int getBlock(float x, float y) const;

    /**
     * Loads the given map
     * @params map an array of arrays of int, represents a map
     */
    void loadMap(const std::vector<std::vector<int>> &map);

  public:
    /**
     * Initializes the Map with the DEFAULT_MAP
     */
    Map();

    /**
     * Initializes the Map with the given map
     */
    Map(std::vector<std::vector<int>> map);

    /**
     * Check if the given Vector position is inside the map
     * @param position the Vector with the position
     * @return true if it is inside, false otherwise
     */
    bool isInsideMap(const Vector &position);

    /**
     * Get the Block value in the position given
     * @param position the Vector with the position
     * @return the value of the position on the map
     */
    int getBlock(const Vector &position) const;

    /**
     * @return the amount of columns of the map
     */
    int getAmountCols() const { return columns; }

    /**
     * @return the amount of rows of the map
     */
    int getAmountRows() const { return rows; }

    void render(SDL_Renderer *renderer) const;

    ~Map();
};

#endif
