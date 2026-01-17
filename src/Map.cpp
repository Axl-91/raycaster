#include "Map.h"
#include "Objects.h"
#include "Walls.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <vector>

std::vector<std::vector<int>> default_level = {
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

std::vector<mapObject> default_objects = {
    {Vector(640, 192), 6}, {Vector(192, 384), 9}, {Vector(192, 448), 9},
    {Vector(192, 320), 9}, {Vector(705, 192), 9},
};

Map::Map() {
    loadMap(default_level);
    loadObjects(default_objects);
}

void Map::loadMap(std::vector<std::vector<int>> &level) {
    if (level.empty()) {
        return;
    }
    size_t cols = level.front().size();

    this->rows = level.size();
    this->columns = cols;

    map = level;
}

void Map::addObject(Vector &position, int type) {
    MapObject obj = {position, type};
    vectObj.push_back(obj);
}

void Map::loadObjects(std::vector<MapObject> objects) {
    for (MapObject object : objects) {
        addObject(object.position, object.type);
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

void Map::sortObjByDist(const Vector &pos) {
    // lambda function to compare distances
    auto compareByDistanceDesc = [&pos](const MapObject &objA,
                                        const MapObject &objB) {
        return pos.distance(objA.position) > pos.distance(objB.position);
    };
    std::sort(vectObj.begin(), vectObj.end(), compareByDistanceDesc);
}

std::vector<MapObject> Map::getObjects() { return vectObj; }

void Map::setObjType(int objType) { objects.setObject(objType); }

void Map::setColObject(int posOffset) { objects.selectSpriteCol(posOffset); }

void Map::renderObject(int posX, int posY, int largo, int alto) {
    objects.render(posX, posY, largo, alto);
}

Map::~Map() {}
