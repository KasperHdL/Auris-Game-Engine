#pragma once

#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"
#include "glm/glm.hpp"
#include "SRE/Mesh.hpp"
#include "src/GameObjects/Components/Sprite.hpp"

using namespace SRE;
class Material{
    public:
        Texture* texture;
        glm::vec4 color;
        Mesh* mesh;

    void set(Sprite* sprite){
       sprite->mesh = mesh;
       sprite->texture = texture;
       sprite->color = color;
    }
};
