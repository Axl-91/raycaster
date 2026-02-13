#include "Config.h"
#include "../utils/YamlUtils.h"
#include <string>
#include <yaml-cpp/yaml.h>

Config::Config(const std::string &filepath) {
    this->yamlNode = YAML::LoadFile(filepath);
    validateFormat();
}

void Config::validateFormat() {
    const std::vector<std::string> gameKeys = {"width", "height", "fullScreen"};
    const std::vector<std::string> spriteTypes = {"walls", "objects", "hud",
                                                  "guns"};
    const std::vector<std::string> spriteKeys = {"path", "cols", "spacing",
                                                 "variants"};

    YAMLUtils::validateValue(this->yamlNode, "game");

    for (const std::string &key : gameKeys) {
        YAMLUtils::validateValue(this->yamlNode["game"], key);
    }

    YAMLUtils::validateValue(this->yamlNode, "sprites");

    for (const std::string &spriteType : spriteTypes) {
        YAMLUtils::validateValue(this->yamlNode["sprites"], spriteType);

        for (const std::string &key : spriteKeys) {
            YAMLUtils::validateValue(this->yamlNode["sprites"][spriteType],
                                     key);
        }
    }
}

int Config::getWinWidth() { return this->yamlNode["game"]["width"].as<int>(); }

int Config::getWinHeight() {
    return this->yamlNode["game"]["height"].as<int>();
}

bool Config::isWinFullScreen() {
    return this->yamlNode["game"]["fullScreen"].as<bool>();
}

const SpriteConfig Config::getWallsSpriteConfig() {
    YAML::Node wallsNode = this->yamlNode["sprites"]["walls"];

    SpriteConfig spriteConfig = {
        wallsNode["path"].as<std::string>(),
        wallsNode["cols"].as<int>(),
        wallsNode["spacing"].as<int>(),
        wallsNode["variants"].as<int>(),
    };

    return spriteConfig;
}

const SpriteConfig Config::getObjectsSpriteConfig() {
    YAML::Node objNode = this->yamlNode["sprites"]["objects"];

    SpriteConfig spriteConfig = {
        objNode["path"].as<std::string>(), objNode["cols"].as<int>(),
        objNode["spacing"].as<int>(), objNode["variants"].as<int>()};

    return spriteConfig;
}

const SpriteConfig Config::getHudSpriteConfig() {
    YAML::Node hudNode = this->yamlNode["sprites"]["hud"];

    SpriteConfig spriteConfig = {
        hudNode["path"].as<std::string>(), hudNode["cols"].as<int>(),
        hudNode["spacing"].as<int>(), hudNode["variants"].as<int>()};

    return spriteConfig;
}

const SpriteConfig Config::getGunsSpriteConfig() {
    YAML::Node gunsNode = this->yamlNode["sprites"]["guns"];

    SpriteConfig spriteConfig = {
        gunsNode["path"].as<std::string>(), gunsNode["cols"].as<int>(),
        gunsNode["spacing"].as<int>(), gunsNode["variants"].as<int>()};

    return spriteConfig;
}
