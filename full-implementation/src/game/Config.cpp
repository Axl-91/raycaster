#include "Config.h"
#include <string>
#include <yaml-cpp/yaml.h>

Config::Config(const std::string &filepath) {
    this->yamlNode = YAML::LoadFile(filepath);
}

const SpriteConfig Config::getWallsSpriteConfig() {
    if (!this->yamlNode["sprites"]["walls"]) {
        std::runtime_error(
            "Invalid Config File: Missing 'sprites/walls' section.");
    }
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
    if (!this->yamlNode["sprites"]["objects"]) {
        std::runtime_error(
            "Invalid Config File: Missing 'sprites/objects' section.");
    }
    YAML::Node objNode = this->yamlNode["sprites"]["objects"];

    SpriteConfig spriteConfig = {
        objNode["path"].as<std::string>(), objNode["cols"].as<int>(),
        objNode["spacing"].as<int>(), objNode["variants"].as<int>()};

    return spriteConfig;
}

const SpriteConfig Config::getHudSpriteConfig() {
    if (!this->yamlNode["sprites"]["hud"]) {
        std::runtime_error(
            "Invalid Config File: Missing 'sprites/hud' section.");
    }
    YAML::Node hudNode = this->yamlNode["sprites"]["hud"];

    SpriteConfig spriteConfig = {
        hudNode["path"].as<std::string>(), hudNode["cols"].as<int>(),
        hudNode["spacing"].as<int>(), hudNode["variants"].as<int>()};

    return spriteConfig;
}

const SpriteConfig Config::getGunsSpriteConfig() {
    if (!this->yamlNode["sprites"]["guns"]) {
        std::runtime_error(
            "Invalid Config File: Missing 'sprites/guns' section.");
    }
    YAML::Node gunsNode = this->yamlNode["sprites"]["guns"];

    SpriteConfig spriteConfig = {
        gunsNode["path"].as<std::string>(), gunsNode["cols"].as<int>(),
        gunsNode["spacing"].as<int>(), gunsNode["variants"].as<int>()};

    return spriteConfig;
}
