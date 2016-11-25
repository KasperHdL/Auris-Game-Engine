#pragma once


#include "glm/glm.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"

#include "Auris/GameObjects/Components/Component.hpp"

using namespace SRE;
class Sprite : public Component{
public:
    Mesh* mesh;
    Texture* texture;
    glm::vec4 color;
    glm::vec2 scale;
        
    virtual void draw();

    ~Sprite(){
    }

    Sprite(GameObject* gameObject):Component(gameObject){
        mesh = Mesh::createCube();
        texture = Texture::getWhiteTexture();
        color = glm::vec4(1,1,1,1);
        scale = glm::vec2(1,1);
    }
};
