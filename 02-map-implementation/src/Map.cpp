#include "Map.h"
#include "Constants.h"
#include "DefaultMapData.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <vector>

Map::Map() { loadMap(DEFAULT_MAP); }

Map::Map(std::vector<std::vector<int>> map) { loadMap(map); }

void Map::loadMap(const std::vector<std::vector<int>> &map) {
    if (map.empty()) {
        return;
    }
    size_t cols = map.front().size();

    this->rows = map.size();
    this->columns = cols;

    this->gridMap = map;
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

int Map::getBlock(float x, float y) const {
    int posX = static_cast<int>(floor(x / BLOCK_SIZE));
    int posY = static_cast<int>(floor(y / BLOCK_SIZE));

    return gridMap[posY][posX];
}

int Map::getBlock(const Vector &v) const {
    return getBlock(v.getX(), v.getY());
}

void Map::render(SDL_Renderer *renderer) const {
    int tileW = SCREEN_WIDTH / this->columns;
    int tileH = SCREEN_HEIGHT / this->rows;

    for (int y = 0; y < this->rows; ++y) {
        for (int x = 0; x < this->columns; ++x) {
            SDL_Rect tile{x * tileW, y * tileH, tileW - 1, tileH - 1};

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_Rect inner{tile.x, tile.y, tileW, tileH};
            SDL_RenderDrawRect(renderer, &inner);

            if (gridMap[y][x] != 0) {
                // Wall
                SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255);
            } else {
                // Empty space
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            }

            SDL_RenderFillRect(renderer, &tile);
        }
    }
}

Map::~Map() {}
