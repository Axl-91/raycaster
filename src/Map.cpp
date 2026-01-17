#include "Map.h"
#include "Objects.h"
#include "Walls.h"
#include "Constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <vector>

Map::Map() {
    loadMap(DEFAULT_MAP);
    loadObjects(DEFAULT_OBJECTS);
}

Map::Map(std::vector<std::vector<int>> map, std::vector<mapObject> objects) {
    loadMap(map);
    loadObjects(objects);
}

void Map::loadMap(const std::vector<std::vector<int>> &map) {
    if (map.empty()) {
        return;
    }
    size_t cols = map.front().size();

    this->rows = map.size();
    this->columns = cols;

    this->map = map;
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

bool Map::isInsideMap(float x, float y) {
    int posX = static_cast<int>(floor(x / BLOCK_SIZE));
    int posY = static_cast<int>(floor(y / BLOCK_SIZE));

    if (posX < 0 || posX >= this->columns)
        return false;

    if (posY < 0 || posY >= this->rows)
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

void Map::setWallType(Vector &vector, bool isDark) {
    int wallType = getBlock(vector) - 1;
    walls.setWall(wallType, isDark);
}

void Map::setColWall(float posX) {
    int intPosX = floor(posX);
    int xOffset = intPosX % BLOCK_SIZE;
    walls.selectSpriteCol(xOffset);
}

void Map::renderWall(int posX, int posY, int width, int height) {
    walls.render(posX, posY, width, height);
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

void Map::setColObject(int posX) { objects.selectSpriteCol(posX); }

void Map::renderObject(int posX, int posY, int largo, int alto) {
    objects.render(posX, posY, largo, alto);
}

Map::~Map() {}
