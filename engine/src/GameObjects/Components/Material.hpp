#pragma once

#include "SRE/Texture.hpp"
#include "SRE/Mesh.hpp"
#include "glm/glm.hpp"

struct Material{
        SRE::Texture* texture;
        glm::vec4 color;
    ~Material() {
        delete texture;
        delete mesh;
    }
};
