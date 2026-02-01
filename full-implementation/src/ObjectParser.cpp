#include "ObjectParser.h"
#include <iostream>
#include <yaml-cpp/yaml.h>

ObjectsData parseObjects(const std::string &filepath) {
    YAML::Node node = YAML::LoadFile(filepath);

    if (!node["objects"]) {
        std::cerr << "Invalid objects file: Missing 'objects' section."
                  << std::endl;
        return {};
    }

    ObjectsData objects;
    for (const auto &obj : node["objects"]) {
        MapObject mapObject;
        mapObject.position = Vector(obj["position"]["x"].as<int>(),
                                    obj["position"]["y"].as<int>());
        mapObject.type = obj["type"].as<int>();
        objects.push_back(mapObject);
    }

    return objects;
}
