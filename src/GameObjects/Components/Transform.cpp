#include "Transform.hpp"
#include "../GameObject.hpp"

glm::mat4 Transform::localTransform() {
    glm::mat4 rz = glm::eulerAngleZ((localRotation));

    glm::mat4 t = glm::translate(glm::mat4(1), vec3(localPosition,0));
    glm::mat4 s = glm::scale(glm::mat4(1), vec3(localScale,1));

    return t * rz * s;
}

glm::mat4 Transform::globalTransform() {
    if(parent == nullptr)
        return localTransform();

    return parent->transform->globalTransform() * localTransform();
}

Transform::~Transform(){
    delete parent;
    parent = nullptr;
}

