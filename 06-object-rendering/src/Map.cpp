#include "Map.h"
#include "Constants.h"
#include "DefaultMapData.h"
#include "DefaultObjects.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
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
    this->gridMap = map;

    this->rows = map.size();
    this->columns = map.front().size();
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

Vector Map::mapToScreen(const Vector &mapPos) const {
    float mapWidth = this->columns * BLOCK_SIZE;
    float mapHeight = this->rows * BLOCK_SIZE;

    int screenX = static_cast<int>((mapPos.getX() / mapWidth) * SCREEN_WIDTH);
    int screenY = static_cast<int>((mapPos.getY() / mapHeight) * SCREEN_HEIGHT);

    return Vector(screenX, screenY);
}

void Map::render(SDL_Renderer *renderer) const {
    constexpr SDL_Color BORDER = {0x36, 0x45, 0x4F, 0xFF};
    constexpr SDL_Color WALL = {0xA5, 0x9C, 0x94, 0xFF};
    constexpr SDL_Color EMPTY = {0x00, 0x00, 0x00, 0x00};

    int tileW = SCREEN_WIDTH / this->columns;
    int tileH = SCREEN_HEIGHT / this->rows;

    for (int y = 0; y < this->rows; ++y) {
        for (int x = 0; x < this->columns; ++x) {
            SDL_Rect tile{x * tileW, y * tileH, tileW - 1, tileH - 1};

            // Border will have a dark gray color
            SDL_SetRenderDrawColor(renderer, BORDER.r, BORDER.g, BORDER.b,
                                   BORDER.a);
            SDL_Rect outter{tile.x, tile.y, tileW, tileH};
            SDL_RenderDrawRect(renderer, &outter);

            if (gridMap[y][x] != 0) {
                // For walls we fill the color with gray
                SDL_SetRenderDrawColor(renderer, WALL.r, WALL.g, WALL.b,
                                       WALL.a);
            } else {
                // For empty space we fill the block with black
                SDL_SetRenderDrawColor(renderer, EMPTY.r, EMPTY.g, EMPTY.b,
                                       EMPTY.a);
            }

            // We render a block with 1px less of width and height
            // to make the last render be used as a border
            SDL_RenderFillRect(renderer, &tile);
        }
    }
}

Map::~Map() {}
