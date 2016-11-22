#include "GameObject.hpp"
#include "Components/Sprite.hpp"
#include "../Constants.hpp"
#include "../Systems/RenderSystem.hpp"
#include "../Utility/Convert.hpp"

GameObject::~GameObject(){
    RenderSystem::deleteSprite(sprite);
}

glm::mat4 GameObject::localTransform() {
    glm::mat4 rz = glm::eulerAngleZ((body->GetAngle()));
    glm::vec2 pos = Convert::vector(body->GetPosition());

    glm::mat4 t = glm::translate(glm::mat4(1), vec3(pos * Constants::METERS_TO_PIXELS,0));
    glm::mat4 s = glm::scale(glm::mat4(1), vec3(sprite->scale,1));

    return t * rz * s;
}

glm::mat4 GameObject::globalTransform() {
    if(parent == nullptr)
        return localTransform();

    return parent->globalTransform() * localTransform();
}


