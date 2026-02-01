#include "MapParser.h"
#include <iostream>
#include <yaml-cpp/yaml.h>

MapData mapParser(const std::string &filepath) {
    YAML::Node yamlNode = YAML::LoadFile(filepath);

    if (!yamlNode["map"]) {
        std::cerr << "Invalid map file: Missing 'map' section." << std::endl;
        return {};
    }

    MapData map;

    for (const auto &row : yamlNode["map"]) {
        std::vector<int> rowData = row.as<std::vector<int>>();
        map.push_back(rowData);
    }

    return map;
}
