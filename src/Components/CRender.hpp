#pragma once

#include "Component.hpp"

#include "glm/glm.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"

using namespace SRE;
class CRender : public Component{
    public:
        Mesh* mesh;
        Shader* shader;
        glm::vec4 color;
        
        void draw();

    protected:

        CRender(GameObject* gameObject):Component(gameObject){}
        friend class GameObject;
};
