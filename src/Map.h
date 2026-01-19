#ifndef __MAP__
#define __MAP__

#include "Objects.h"
#include "Vector.h"
#include "Walls.h"
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
    std::vector<std::vector<int>> map;

    Objects objects;
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
    int getBlock(float x, float y);

    /**
     * Adds an object to the Map
     * @params position a Vector with the position of the object
     * @params type the type of the object to be added
     */
    void addObject(Vector &position, int type);

    /**
     * Loads the given map
     * @params map an array of arrays of int, represents a map
     */
    void loadMap(const std::vector<std::vector<int>> &map);

    /**
     * Loads a the given objects
     * @params objects an array of mapObject
     */
    void loadObjects(std::vector<mapObject> objects);

  public:
    /**
     * Initializes the Map with the DEFAULT_MAP and DEFAULT_OBJECTS
     */
    Map();

    /**
     * Initializes the Map with the given map and object
     */
    Map(std::vector<std::vector<int>> map, std::vector<MapObject> objects = {});

    /**
     * Set renderer for the map
     * @param renderer SDL renderer to use for creating textures
     */
    void setRenderer(SDL_Renderer *renderer);

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
    int getBlock(const Vector &position);

    /**
     * Sort the objects by distance with the playerPos
     * @param playerPos the Vector position of the player
     */
    void sortObjByDist(const Vector &playerPos);

    /**
     * @return All the objects in the map
     */
    std::vector<MapObject> getObjects();

    /**
     * Set the object type
     * @param position the position in the map where the object is
     */
    void setObjType(int objType);

    /**
     * Set the object column to render
     * @param posX the x position that will be render as a 1px column
     */
    void setColObject(int posX);

    /**
     * Render the object in the given position
     */
    void renderObject(int posX, int posY, int largo, int alto);

    ~Map();
};

#endif
