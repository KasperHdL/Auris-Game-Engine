#pragma once

#include "SRE/Texture.hpp"
#include "SRE/Mesh.hpp"
#include "glm/glm.hpp"

namespace Auris{
struct Material{
    SRE::Texture* texture;
    glm::vec4 color;
    SRE::Mesh* mesh;

    ~Material() {
    }
};
}
