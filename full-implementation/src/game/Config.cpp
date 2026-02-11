#include "Config.h"
#include <string>
#include <yaml-cpp/yaml.h>

namespace {
void validateValue(YAML::Node node, std::string value) {
    if (!node[value]) {
        std::ostringstream oss;
        oss << "Invalid Config Format: Missing " << value << " section.";
        throw std::runtime_error(oss.str());
    }
}
} // namespace

Config::Config(const std::string &filepath) {
    this->yamlNode = YAML::LoadFile(filepath);
    validateFormat();
}

void Config::validateFormat() {
    validateValue(this->yamlNode, "game");
    validateValue(this->yamlNode["game"], "width");
    validateValue(this->yamlNode["game"], "height");
    validateValue(this->yamlNode["game"], "fullScreen");

    validateValue(this->yamlNode, "sprites");

    validateValue(this->yamlNode["sprites"], "walls");
    validateValue(this->yamlNode["sprites"]["walls"], "path");
    validateValue(this->yamlNode["sprites"]["walls"], "cols");
    validateValue(this->yamlNode["sprites"]["walls"], "spacing");
    validateValue(this->yamlNode["sprites"]["walls"], "variants");

    validateValue(this->yamlNode["sprites"], "objects");
    validateValue(this->yamlNode["sprites"]["objects"], "path");
    validateValue(this->yamlNode["sprites"]["objects"], "cols");
    validateValue(this->yamlNode["sprites"]["objects"], "spacing");
    validateValue(this->yamlNode["sprites"]["objects"], "variants");

    validateValue(this->yamlNode["sprites"], "hud");
    validateValue(this->yamlNode["sprites"]["hud"], "path");
    validateValue(this->yamlNode["sprites"]["hud"], "cols");
    validateValue(this->yamlNode["sprites"]["hud"], "spacing");
    validateValue(this->yamlNode["sprites"]["hud"], "variants");

    validateValue(this->yamlNode["sprites"], "guns");
    validateValue(this->yamlNode["sprites"]["guns"], "path");
    validateValue(this->yamlNode["sprites"]["guns"], "cols");
    validateValue(this->yamlNode["sprites"]["guns"], "spacing");
    validateValue(this->yamlNode["sprites"]["guns"], "variants");
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
