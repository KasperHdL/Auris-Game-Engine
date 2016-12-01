#include "Auris/GameObjects/GameObject.hpp"
#include "Auris/GameObjects/Components/Sprite.hpp"
#include "Auris/Constants.hpp"
#include "Auris/Engine.hpp"
#include "Auris/Utilities/Convert.hpp"
#include "Auris/Systems/RenderSystem.hpp"

using namespace Auris;

GameObject::GameObject(){}

GameObject::~GameObject(){
    RenderSystem::deleteSprite(sprite);
    Engine::removeGameObject(this);
}

glm::mat4 GameObject::localTransform() {
    glm::mat4 rz = glm::eulerAngleZ(body->GetAngle());
    glm::vec2 pos = Convert::toGlm(body->GetPosition());
    glm::mat4 t = glm::translate(glm::mat4(1), vec3(pos * Constants::METERS_TO_PIXELS,0));
    glm::mat4 s = glm::scale(glm::mat4(1), vec3(sprite->scale,1));

    return t * rz * s;
}

glm::mat4 GameObject::globalTransform() {
    if(parent == nullptr)
        return localTransform();

    return parent->globalTransform() * localTransform();
}


