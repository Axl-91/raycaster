#include "MapParser.h"
#include <iostream>
#include <yaml-cpp/yaml.h>

MapParser::MapParser(const std::string &filepath) {
    this->yamlNode = YAML::LoadFile(filepath);
}

MapData MapParser::getMap() {
    if (!this->yamlNode["map"]) {
        std::cerr << "Invalid map file: Missing 'map' section." << std::endl;
        return {};
    }

    MapData map;

    for (const auto &row : this->yamlNode["map"]["tiles"]) {
        std::vector<int> rowData = row.as<std::vector<int>>();
        map.push_back(rowData);
    }
    return map;
}

Vector MapParser::getMapSize() {
    if (!this->yamlNode["map"]) {
        std::cerr << "Invalid map file: Missing 'map' section." << std::endl;
        return {};
    }

    int columns = this->yamlNode["map"]["size"]["columns"].as<int>();
    int rows = this->yamlNode["map"]["size"]["rows"].as<int>();

    return Vector(columns, rows);
}

ObjectsData MapParser::getObjects() {
    if (!this->yamlNode["objects"]) {
        std::cerr << "Invalid objects file: Missing 'objects' section."
                  << std::endl;
        return {};
    }

    ObjectsData objects;

    for (const auto &obj : this->yamlNode["objects"]) {
        MapObject mapObject;
        mapObject.position = Vector(obj["position"]["x"].as<float>(),
                                    obj["position"]["y"].as<float>());
        mapObject.type = obj["type"].as<int>();
        objects.push_back(mapObject);
    }
    return objects;
}

PlayersPos MapParser::getPlayersPos() {
    if (!this->yamlNode["players"]) {
        std::cerr << "Invalid objects file: Missing 'objects' section."
                  << std::endl;
        return {};
    }

    PlayersPos playersPos;

    for (const auto &obj : this->yamlNode["players"]) {
        Vector position;
        position = Vector(obj["position"]["x"].as<float>(),
                          obj["position"]["y"].as<float>());

        playersPos.push_back(position);
    }
    return playersPos;
}
