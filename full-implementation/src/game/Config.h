#ifndef CONFIG_H
#define CONFIG_H

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

    /**
     * Validates the format of the config file
     */
    void validateFormat();

  public:
    Config(const std::string &path = "resources/config.yaml");

    /**
     * @return default windows width from the config file
     */
    int getWinWidth();

    /**
     * @return default windows height from the config file
     */
    int getWinHeight();

    /**
     * @return walls sprite config
     */
    const SpriteConfig getWallsSpriteConfig();

    /**
     * @return objects sprite config
     */
    const SpriteConfig getObjectsSpriteConfig();

    /**
     * @return hud sprite config
     */
    const SpriteConfig getHudSpriteConfig();

    /**
     * @return guns sprite config
     */
    const SpriteConfig getGunsSpriteConfig();
};

#endif
