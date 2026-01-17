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

    int rows = 15;
    int columns = 20;
    int map[15][20];

    Walls walls;
    Objects objects;
    std::vector<mapObject> vectObj;

    bool isInsideMap(float x, float y);

    int getBlock(float x, float y);

  public:
    Map();

    void loadMap(int lvl[15][20]);

    void setRenderer(SDL_Renderer *renderer);

    int getBlockSize();

    bool isInsideMap(const Vector &posicion);

    int getBlock(const Vector &posicion);

    void setWallType(Vector &posicion, bool dark);

    void setColWall(float pos);

    void renderWall(int posX, int posY, int largo, int alto);

    void addObject(Vector &posicion, int tipo);

    void sortObjByDist(Vector &pos);

    std::vector<MapObject> getObjects();

    void setObjType(int objType);

    void setColObject(int pos);

    void renderObject(int posX, int posY, int largo, int alto);

    ~Map();
};

#endif
