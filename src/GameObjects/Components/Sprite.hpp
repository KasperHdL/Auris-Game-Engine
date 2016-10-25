#pragma once

#include "Component.hpp"
#include "glm/glm.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"

using namespace SRE;
class Sprite : public Component{
    public:
        Mesh* mesh;
        glm::vec4 color;
        glm::vec2 scale;
        
        virtual void draw();

        ~Sprite(){
            delete mesh;
            mesh = nullptr;
        }

        Sprite(GameObject* gameObject):Component(gameObject){}
};


class SpriteTexture : public Sprite{
    public:
        Texture* texture;

        ~SpriteTexture(){
            delete texture;
            texture = nullptr;
        }

        void draw() override;

        SpriteTexture(GameObject* gameObject):Sprite(gameObject){} 

};
