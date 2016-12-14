#pragma once

#include "SRE/Texture.hpp"
#include "SRE/Mesh.hpp"
#include "glm/glm.hpp"

namespace Auris{
class Material{
public:
    SRE::Texture* texture;
    SRE::Texture* normalMap = nullptr;
    SRE::Shader* shader;
    glm::vec4 color;
};
}
