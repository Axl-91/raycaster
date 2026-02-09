#include "MapParser.h"
#include <stdexcept>
#include <yaml-cpp/yaml.h>

namespace {
void validateValue(YAML::Node node, std::string value) {
    if (!node[value]) {
        std::ostringstream oss;
        oss << "Invalid Map Format: Missing " << value << " section.";
        throw std::runtime_error(oss.str());
    }
}
} // namespace

MapParser::MapParser(const std::string &filepath) {
    this->yamlNode = YAML::LoadFile(filepath);
    validateFormat();
}

void MapParser::validateFormat() {
    validateValue(this->yamlNode, "map");
    validateValue(this->yamlNode["map"], "tiles");
    validateValue(this->yamlNode["map"], "size");
    validateValue(this->yamlNode["map"]["size"], "columns");
    validateValue(this->yamlNode["map"]["size"], "rows");

    validateValue(this->yamlNode, "objects");

    for (const auto &obj : this->yamlNode["objects"]) {
        validateValue(obj, "position");
        validateValue(obj["position"], "x");
        validateValue(obj["position"], "y");
        validateValue(obj, "type");
    }

    validateValue(this->yamlNode, "players");

    for (const auto &player : this->yamlNode["players"]) {
        validateValue(player, "position");
        validateValue(player["position"], "x");
        validateValue(player["position"], "y");
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
