#pragma once

#include "Component.hpp"

#include "glm/glm.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"

using namespace SRE;
class CSprite : public Component{
    public:
        Mesh* mesh;
        glm::vec4 color;
        
        virtual void draw();

    protected:

        CSprite(GameObject* gameObject):Component(gameObject){}
        friend class GameObject;
};


class CSpriteTexture : public CSprite{
    public:
        Texture* texture;

        void draw() override;

    protected:
        CSpriteTexture(GameObject* gameObject):CSprite(gameObject){} 
        friend class GameObject;

};
