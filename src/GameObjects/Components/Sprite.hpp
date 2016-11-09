#pragma once

#include "Component.hpp"
#include "glm/glm.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"
#include "../../Material.hpp"

using namespace SRE;
class Sprite : public Component{
    public:
        Material* material;
        Mesh* mesh;

        glm::vec2 scale;
        
        virtual void draw();

        ~Sprite(){
            delete mesh;
            mesh = nullptr;
        }

        Sprite(GameObject* gameObject):Component(gameObject){}
};
