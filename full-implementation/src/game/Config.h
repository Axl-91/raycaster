#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <yaml-cpp/node/node.h>

typedef struct SpriteConfig {
    const std::string path;
    const int columns;
    const int spacing;
    const int variants;
} WallsConfig;

class Config {
  private:
    YAML::Node yamlNode;

  public:
    Config(const std::string &path = "resources/config.yaml");

    int getWinWidth();

    int getWinHeight();

    const SpriteConfig getWallsSpriteConfig();

    const SpriteConfig getObjectsSpriteConfig();

    const SpriteConfig getHudSpriteConfig();

    const SpriteConfig getGunsSpriteConfig();
};

#endif
