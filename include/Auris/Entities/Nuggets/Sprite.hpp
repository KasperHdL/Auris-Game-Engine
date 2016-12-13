#pragma once


#include "glm/glm.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"

#include "Auris/Utilities/Shader.hpp"
#include "Auris/Entities/Nugget.hpp"
#include "Auris/Entities/Nuggets/Material.hpp"

namespace Auris{
using namespace SRE;
class Sprite : public Nugget{
public:
    Mesh* mesh;
    SRE::Shader* shader;
    Texture* texture;
    Texture* normalMap;
    glm::vec4 color;
        
    virtual void draw();

    ~Sprite();
    Sprite(Entity* entity):Nugget(entity){
        mesh = Mesh::createCube();
        texture = Texture::getWhiteTexture();
        normalMap = nullptr;
        shader = SRE::Shader::getUnlitSprite();
        color = glm::vec4(1,1,1,1);
    }

    Sprite(Entity* entity, Material* material):Nugget(entity){
        setMaterial(material);
    }

    void setMaterial(Material* material){
        mesh = material->mesh;
        texture = material->texture;
        normalMap = material->normalMap;
        if(normalMap == nullptr)
            shader = SRE::Shader::getUnlitSprite();
        else
            shader = Auris::Shader::getLitSprite();
        color = material->color;

    }
};
}
