#ifndef __MAP__
#define __MAP__

#include "../utils/Vector.h"
#include "MapParser.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

class Map {
  private:
    int rows = -1;
    int columns = -1;

    MapData gridMap;
    ObjectsData vectObj;
    PlayersPos playersPos;

    /**
     * Check if the x and y positions are inside the map array
     * @params x the X value in the array
     * @params y the Y value in the array
     */
    bool isInsideMap(float x, float y) const;

    /**
     * Gets the block in the position x and y
     * @params x the X value in the array
     * @params y the Y value in the array
     */
    int getBlock(float x, float y) const;

    /**
     * Adds an object to the Map
     * @params position a Vector with the position of the object
     * @params type the type of the object to be added
     */
    void addObject(Vector &position, int type);

    /**
     * Sort the objects by distance with the playerPos
     * @param playerPos the Vector position of the player
     */
    void sortObjByDist(const Vector &playerPos);

    /**
     * Loads the given map
     * @params map an array of arrays of int, represents a map
     */
    void loadMap(const std::string &mapPath);

    /**
     * Loads a the given objects
     * @params objects an array of mapObject
     */
    void loadObjects(const std::string &objectsPath);

  public:
    /**
     * Initializes the Map with the given map and object
     */
    Map(std::string mapPath = "resources/maps/defaultMap.yaml");

    Vector getInitPos();

    /**
     * Check if the given Vector position is inside the map
     * @param position the Vector with the position
     * @return true if it is inside, false otherwise
     */
    bool isInsideMap(const Vector &position) const;

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

    /**
     * @return All the objects in the map sorted based by the distance from the
     * player
     */
    std::vector<MapObject> getObjectsSorted(const Vector &playerPos);

    Map(const Map &copy) = delete;
    Map operator=(const Map &copy) = delete;

    ~Map();
};

#endif
