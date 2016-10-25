#include "GameObject.hpp"
#include "Components/Transform.hpp"

GameObject::GameObject(vec2 position, float rotation, vec2 scale){
    transform = make_shared<Transform>(this);
    transform->localPosition = position;
    transform->localRotation = rotation;
    transform->localScale = scale;
}
