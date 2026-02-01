#include "Map.h"
#include "../utils/Constants.h"
#include "MapParser.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <vector>

Map::Map() { loadMap(DEFAULT_MAP); }

Map::Map(std::string mapPath) { loadMap(mapPath); }

void Map::loadMap(const std::string &mapPath) {
    MapParser mapParser = MapParser(mapPath);

    this->gridMap = mapParser.getMap();

    Vector mapSize = mapParser.getMapSize();

    this->columns = mapSize.getX();
    this->rows = mapSize.getY();

    ObjectsData objects = mapParser.getObjects();

    for (MapObject object : objects) {
        MapObject obj = {object.position, object.type};
        this->vectObj.push_back(obj);
    }

    this->playersPos = mapParser.getPlayersPos();
}

Vector Map::getInitPos() {
    Vector pos = this->playersPos.back();
    this->playersPos.pop_back();

    return pos;
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
