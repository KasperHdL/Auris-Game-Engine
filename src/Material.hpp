#pragma once

#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"
#include "glm/glm.hpp"

using namespace SRE;
class Material{
    public:
        Shader* shader;
        Texture* texture;
        glm::vec4 color;

    void set(){
        shader = Shader::getUnlitSprite();
        shader->set("color",color);
        shader->set("tex",texture);
    }
};
