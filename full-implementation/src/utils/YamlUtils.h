#ifndef YAML_UTILS_H
#define YAML_UTILS_H

#include <sstream>
#include <stdexcept>
#include <string>
#include <yaml-cpp/yaml.h>

namespace YAMLUtils {
inline void validateValue(const YAML::Node &node, const std::string &value) {
    if (!node[value]) {
        std::string identifier = node["fileName"]
                                     ? node["fileName"].as<std::string>()
                                     : "unknown file";

        std::ostringstream oss;
        oss << "Invalid YAML format in '" << identifier << "': Missing "
            << value << " section.";
        throw std::runtime_error(oss.str());
    }
}
} // namespace YAMLUtils

#endif
