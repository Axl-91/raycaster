#include "MapParser.h"
#include "../utils/YamlUtils.h"
#include <yaml-cpp/yaml.h>

MapParser::MapParser(const std::string &filepath) {
    this->yamlNode = YAML::LoadFile(filepath);
    validateFormat();
}

void MapParser::validateFormat() {
    const std::vector<std::string> mapKeys = {"tiles", "size"};
    const std::vector<std::string> sizeKeys = {"columns", "rows"};
    const std::vector<std::string> objKeys = {"position", "type"};
    const std::vector<std::string> posKeys = {"x", "y"};

    YAMLUtils::validateValue(this->yamlNode, "map");

    for (const std::string &key : mapKeys) {
        YAMLUtils::validateValue(this->yamlNode["map"], key);
    }
    for (const std::string &key : sizeKeys) {
        YAMLUtils::validateValue(this->yamlNode["map"]["size"], key);
    }

    YAMLUtils::validateValue(this->yamlNode, "objects");

    for (const auto &obj : this->yamlNode["objects"]) {
        for (const std::string &key : objKeys) {
            YAMLUtils::validateValue(obj, key);
        }
        for (const std::string &key : posKeys) {
            YAMLUtils::validateValue(obj["position"], key);
        }
    }

    YAMLUtils::validateValue(this->yamlNode, "players");

    for (const auto &player : this->yamlNode["players"]) {
        YAMLUtils::validateValue(player, "position");

        for (const std::string &key : posKeys) {
            YAMLUtils::validateValue(player["position"], key);
        }
    }
}

MapData MapParser::getMap() {
    MapData map;

    for (const auto &row : this->yamlNode["map"]["tiles"]) {
        std::vector<int> rowData = row.as<std::vector<int>>();
        map.push_back(rowData);
    }
    return map;
}

Vector MapParser::getMapSize() {
    int columns = this->yamlNode["map"]["size"]["columns"].as<int>();
    int rows = this->yamlNode["map"]["size"]["rows"].as<int>();

    return Vector(columns, rows);
}

ObjectsData MapParser::getObjects() {
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
    PlayersPos playersPos;

    for (const auto &player : this->yamlNode["players"]) {
        Vector position;
        position = Vector(player["position"]["x"].as<float>(),
                          player["position"]["y"].as<float>());

        playersPos.push_back(position);
    }
    return playersPos;
}
