#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include "../utils/Vector.h"
#include <string>
#include <vector>
#include <yaml-cpp/node/node.h>

typedef struct mapObject {
    Vector position;
    int type;
} MapObject;

using MapData = std::vector<std::vector<int>>;
using ObjectsData = std::vector<MapObject>;
using PlayersPos = std::vector<Vector>;

class MapParser {
  private:
    YAML::Node yamlNode;

    /**
     * Validates the format of the map file
     */
    void validateFormat();

  public:
    MapParser(const std::string &filepath);

    /**
     * @return a vector of vectors of int representing the map
     */
    MapData getMap();

    /**
     * @return a vector of vectors of int representing the map dimensions
     */
    Vector getMapSize();

    /**
     * @return a vector of the objects data
     */
    ObjectsData getObjects();

    /**
     * @return a vector of 'Vector' that represents the position of the players
     * on the map
     */
    PlayersPos getPlayersPos();
};

#endif
