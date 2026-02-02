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

  public:
    MapParser(const std::string &filepath);

    /**
     * Function that load a map from a YAML file
     * @return a vector of vectors of int representing the map
     */
    MapData getMap();

    Vector getMapSize();

    ObjectsData getObjects();

    PlayersPos getPlayersPos();
};

#endif
