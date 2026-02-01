#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include <string>
#include <vector>

using MapData = std::vector<std::vector<int>>;

/**
 * Function that load a map from a YAML file
 * @return a vector of vectors of int representing the map
 */
MapData mapParser(const std::string &filepath);

#endif
