#ifndef OBJECT_PARSER_H
#define OBJECT_PARSER_H

#include "../utils/Vector.h"
#include <string>
#include <vector>

typedef struct mapObject {
    Vector position;
    int type;
} MapObject;

using ObjectsData = std::vector<MapObject>;

ObjectsData parseObjects(const std::string &filepath);

#endif
