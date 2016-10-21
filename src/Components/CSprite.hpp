#pragma once

#include "Component.hpp"

#include "glm/glm.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"

using namespace SRE;
class CSprite : public Component{
    public:
        Mesh* mesh;
        glm::vec4 color;
        
        virtual void draw();

        ~CSprite(){
            delete mesh;
            mesh = nullptr;
        }

    protected:

        CSprite(GameObject* gameObject):Component(gameObject){}
        friend class GameObject;
};


class CSpriteTexture : public CSprite{
    public:
        Texture* texture;

        ~CSpriteTexture(){
            delete texture;
            texture = nullptr;
        }


        void draw() override;

    protected:
        CSpriteTexture(GameObject* gameObject):CSprite(gameObject){} 
        friend class GameObject;

};
