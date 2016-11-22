#pragma once

#include "picojson.h"
#include <fstream>

using namespace std;

class GameObjectDescriptor {
public:
    // Uniquely defines a game object
    int uniqueId;

    string name;

    glm::vec4 color;

    // transform
    // position relative to parent
    glm::vec3 position;

    // rotation relative to parent
    glm::vec3 rotationEuler;

    // scale relative to parent
    glm::vec3 scale;

    // parent id (-1 means no parent)
    int parentId;
};
