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
    static constexpr int BLOCK_SIZE = 64;

    int rows = -1;
    int columns = -1;
    std::vector<std::vector<int>> map;

    Walls walls;
    Objects objects;
    std::vector<mapObject> vectObj;

    bool isInsideMap(float x, float y);

    int getBlock(float x, float y);

    void addObject(Vector &posicion, int tipo);

  public:
    Map();

    void loadMap(std::vector<std::vector<int>> &level);

    void loadObjects(std::vector<mapObject> objects);

    void setRenderer(SDL_Renderer *renderer);

    int getBlockSize();

    bool isInsideMap(const Vector &posicion);

    int getBlock(const Vector &posicion);

    void setWallType(Vector &posicion, bool dark);

    void setColWall(float pos);

    void renderWall(int posX, int posY, int largo, int alto);

    void sortObjByDist(const Vector &pos);

    std::vector<MapObject> getObjects();

    void setObjType(int objType);

    void setColObject(int pos);

    void renderObject(int posX, int posY, int largo, int alto);

    ~Map();
};

#endif
