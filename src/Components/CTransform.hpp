#pragma once

#include "Component.hpp"

#include "glm/glm.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

class CTransform : public Component{
    public:
        GameObject* parent;

        vec3 localPosition;
        vec3 localScale;
        vec3 localRotation;

        glm::mat4 localTransform() {
            glm::mat4 rx = glm::eulerAngleX((localRotation.x));
            glm::mat4 ry = glm::eulerAngleY((localRotation.y));
            glm::mat4 rz = glm::eulerAngleZ((localRotation.z));

            glm::mat4 t = glm::translate(glm::mat4(1), localPosition);
            glm::mat4 s = glm::scale(glm::mat4(1), localScale);

            return t * (rz * ry * rx) * s;
        }

        glm::mat4 globalTransform() {
            if(parent == nullptr)
                return localTransform();

            return parent->transform->globalTransform() * localTransform();
        }

    protected:

        CTransform(GameObject *gameObject):Component(gameObject){}

        friend class GameObject;

};


