#pragma once

#include "Component.hpp"

#include "glm/glm.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

class CTransform : public Component{
    public:
        GameObject* parent;

        vec2 localPosition;
        vec2 localScale;
        float localRotation;

        glm::mat4 localTransform();
        glm::mat4 globalTransform();

    protected:

        CTransform(GameObject *gameObject):Component(gameObject){
            localRotation = 0;
            localScale = vec2(10,10);

        }

        friend class GameObject;

};


