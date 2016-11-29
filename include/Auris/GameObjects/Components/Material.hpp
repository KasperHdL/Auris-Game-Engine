#pragma once

#include "SRE/Texture.hpp"
#include "SRE/Mesh.hpp"
#include "glm/glm.hpp"

struct Material{
    SRE::Texture* texture;
    glm::vec4 color;
    SRE::Mesh* mesh;

    ~Material() {
        delete texture;
        delete mesh;
    }
};
