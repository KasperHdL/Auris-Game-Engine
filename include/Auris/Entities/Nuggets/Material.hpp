#pragma once

#include "SRE/Texture.hpp"
#include "SRE/Mesh.hpp"
#include "glm/glm.hpp"

namespace Auris{

//! The Material class
    /*! To hold all material related stuff
    */
class Material{
public:
    SRE::Texture* texture; /*!< A Texture pointer: texture. Texture of the material. */
    SRE::Texture* normalMap = nullptr; /*!< A Texture pointer: normalMap. Normalmap of the material (default is nullptr). */
    SRE::Shader* shader; /*!< A Shader pointer: shader. Shader of the material. */
    glm::vec4 color; /*!< A vec4 value: color. Color of the material. */
};
}
