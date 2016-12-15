#pragma once


#include "glm/glm.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Texture.hpp"

#include "Auris/Utilities/Mesh.hpp"
#include "Auris/Constants.hpp"
#include "Auris/Utilities/Shader.hpp"
#include "Auris/Entities/Nugget.hpp"
#include "Auris/Entities/Nuggets/Material.hpp"

#include <iostream>
namespace Auris{
class Sprite : public Nugget{
public:
    Mesh* mesh;
    Material material;

    glm::vec3 offset = glm::vec3(0);

    virtual void draw();

    ~Sprite();

    Sprite(Entity* entity, SRE::Texture* texture = nullptr, SRE::Texture* normalMap = nullptr, Mesh* mesh = nullptr):Nugget(entity){
        if(mesh == nullptr)
            this->mesh = Mesh::createQuad();
        else
            this->mesh = mesh;

        if(texture == nullptr)
            material.texture = SRE::Texture::getWhiteTexture();
        else
            material.texture = texture;

        material.normalMap = normalMap;
        material.color = glm::vec4(1);

        if(normalMap == nullptr)
            material.shader = (Shader*) Shader::getUnlitSprite();
        else
            material.shader = (Shader*) Shader::getLitSprite();

    }

    Sprite(Entity* entity, SRE::Texture* texture, Mesh* mesh = nullptr):Nugget(entity){
        Sprite(entity, texture, nullptr, mesh);
    }

    //! Return the width of the currently assigned mesh in pixels
    float getWidth(){
        return mesh->width;
    }

    //! Return the height of the currently assigned mesh in pixels
    float getHeight(){
        return mesh->height;
    }
};
}
