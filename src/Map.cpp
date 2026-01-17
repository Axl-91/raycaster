#include "Map.h"
#include "Objects.h"
#include "Walls.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstddef>
#include <vector>

int lvl1[15][20] = {
    {34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
     34, 34, 34, 34, 34, 34, 34, 34, 34, 34},
    {34, 00, 00, 00, 00, 00, 00, 00, 00, 00,
     00, 00, 00, 00, 00, 00, 00, 00, 00, 34},
    {34, 00, 00, 00, 00, 00, 00, 00, 00, 00,
     00, 00, 00, 00, 00, 00, 00, 00, 00, 34},
    {34, 35, 49, 35, 35, 49, 35, 35, 00, 00,
     00, 00, 00, 36, 36, 00, 00, 00, 00, 34},
    {34, 00, 00, 00, 00, 00, 00, 00, 00, 00,
     00, 00, 00, 36, 36, 00, 00, 00, 00, 34},
    {34, 00, 00, 00, 00, 00, 00, 00, 00, 00,
     00, 00, 00, 00, 00, 00, 00, 00, 00, 34},
    {34, 00, 00, 00, 00, 00, 00, 00, 00, 00,
     00, 00, 00, 00, 00, 00, 00, 00, 00, 34},
    {34, 00, 00, 00, 00, 00, 00, 00, 00, 00,
     00, 00, 00, 00, 00, 00, 00, 00, 00, 34},
    {34, 34, 34, 34, 34, 34, 00, 00, 34, 34,
     34, 34, 00, 00, 00, 00, 00, 34, 34, 34},
    {34, 00, 00, 00, 00, 00, 00, 00, 34, 34,
     00, 00, 00, 00, 00, 00, 00, 00, 00, 34},
    {34, 00, 00, 00, 00, 00, 00, 00, 34, 34,
     00, 00, 00, 00, 00, 00, 00, 00, 00, 34},
    {34, 00, 00, 00, 00, 00, 00, 00, 34, 34,
     00, 00, 00, 00, 00, 00, 00, 00, 00, 34},
    {34, 00, 00, 00, 00, 00, 00, 00, 34, 34,
     00, 00, 00, 00, 00, 00, 00, 00, 00, 34},
    {34, 00, 00, 00, 00, 00, 00, 00, 34, 34,
     00, 00, 00, 00, 00, 00, 00, 00, 00, 34},
    {34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
     34, 34, 34, 34, 34, 34, 34, 34, 34, 34},
};

MapObject light1 = {Vector(640, 192), 6};
MapObject column1 = {Vector(192, 384), 9};
MapObject column2 = {Vector(192, 448), 9};
MapObject column3 = {Vector(192, 320), 9};
MapObject column4 = {Vector(705, 192), 9};

Map::Map() {
    loadMap(lvl1);
    addObject(light1.position, light1.type);
    addObject(column1.position, column1.type);
    addObject(column2.position, column2.type);
    addObject(column3.position, column3.type);
    addObject(column4.position, column4.type);
}

void Map::loadMap(int lvl[15][20]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            map[i][j] = lvl[i][j];
        }
    }
}

void Map::setRenderer(SDL_Renderer *renderer) {
    walls.setRenderer(renderer);
    objects.setRenderer(renderer);
}

int Map::getBlockSize() { return BLOCK_SIZE; }

bool Map::isInsideMap(float x, float y) {

    int posX = static_cast<int>(floor(x / BLOCK_SIZE));
    int posY = static_cast<int>(floor(y / BLOCK_SIZE));

    if (posX < 0 || posX >= columns)
        return false;

    if (posY < 0 || posY >= rows)
        return false;

    return true;
}

bool Map::isInsideMap(const Vector &vector) {
    return isInsideMap(vector.getX(), vector.getY());
}

int Map::getBlock(float x, float y) {
    int posX = static_cast<int>(floor(x / BLOCK_SIZE));
    int posY = static_cast<int>(floor(y / BLOCK_SIZE));

    return map[posY][posX];
}

int Map::getBlock(const Vector &v) { return getBlock(v.getX(), v.getY()); }

void Map::setWallType(Vector &vector, bool dark) {
    int wallType = getBlock(vector) - 1;
    walls.setWall(wallType, dark);
}

void Map::setColWall(float pos) {
    int rayInt = floor(pos);
    int posWall = rayInt % BLOCK_SIZE;
    walls.selectSpriteCol(posWall);
}

void Map::renderWall(int posX, int posY, int largo, int alto) {
    walls.render(posX, posY, largo, alto);
}

void Map::addObject(Vector &posicion, int tipo) {
    MapObject obj = {posicion, tipo};
    vectObj.push_back(obj);
}

void addInOrderByDist(std::vector<MapObject> &v, MapObject &obj, Vector &pos) {
    float dist = pos.distance(obj.position);
    for (auto i = v.begin(); i != v.end(); ++i) {
        MapObject objVec = *i;
        float distV = pos.distance(objVec.position);
        if (dist > distV) {
            v.insert(i, obj);
            return;
        }
    }
    v.push_back(obj);
}

void Map::sortObjByDist(Vector &pos) {
    std::vector<MapObject> vectorAux;

    for (MapObject obj : vectObj) {
        addInOrderByDist(vectorAux, obj, pos);
    }
    vectObj.swap(vectorAux);
}

std::vector<MapObject> Map::getObjects() { return vectObj; }

void Map::setObjType(int objType) { objects.setObject(objType); }

void Map::setColObject(int posOffset) { objects.selectSpriteCol(posOffset); }

void Map::renderObject(int posX, int posY, int largo, int alto) {
    objects.render(posX, posY, largo, alto);
}

Map::~Map() {}
