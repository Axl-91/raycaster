#include "Map.h"
#include "Constants.h"
#include "MapParser.h"
#include "ObjectParser.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <vector>

Map::Map() {
    loadMap(DEFAULT_MAP);
    loadObjects(DEFAULT_OBJECTS);
}

Map::Map(std::string mapPath, std::string objectsPath) {
    loadMap(mapPath);
    loadObjects(objectsPath);
}

void Map::loadMap(const std::string &mapPath) {
    this->gridMap = mapParser(mapPath);

    this->rows = this->gridMap.size();
    this->columns = this->gridMap.front().size();
}

void Map::addObject(Vector &position, int type) {
    MapObject obj = {position, type};
    vectObj.push_back(obj);
}

void Map::loadObjects(const std::string &objectsPath) {
    ObjectsData objects = parseObjects(objectsPath);

    for (MapObject object : objects) {
        addObject(object.position, object.type);
    }
}

bool Map::isInsideMap(float x, float y) const {
    int posX = static_cast<int>(floor(x / BLOCK_SIZE));
    int posY = static_cast<int>(floor(y / BLOCK_SIZE));

    bool xInvalid = posX < 0 || posX >= this->columns;
    bool yInvalid = posY < 0 || posY >= this->rows;

    if (xInvalid || yInvalid)
        return false;

    return true;
}

bool Map::isInsideMap(const Vector &vector) const {
    return isInsideMap(vector.getX(), vector.getY());
}

int Map::getBlock(float x, float y) const {
    int posX = static_cast<int>(floor(x / BLOCK_SIZE));
    int posY = static_cast<int>(floor(y / BLOCK_SIZE));

    return gridMap[posY][posX];
}

int Map::getBlock(const Vector &v) const {
    return getBlock(v.getX(), v.getY());
}

void Map::sortObjByDist(const Vector &pos) {
    // lambda function to compare distances
    auto compareByDistanceDesc = [&pos](const MapObject &objA,
                                        const MapObject &objB) {
        return pos.distance(objA.position) > pos.distance(objB.position);
    };
    std::sort(vectObj.begin(), vectObj.end(), compareByDistanceDesc);
}

std::vector<MapObject> Map::getObjectsSorted(const Vector &playerPos) {
    sortObjByDist(playerPos);
    return vectObj;
}

Map::~Map() {}
