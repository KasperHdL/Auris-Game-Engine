#include "GameObject.hpp"

#include "Components/CTransform.hpp"
#include "Components/CSprite.hpp"

GameObject::GameObject(){
    components = vector<shared_ptr<Component>>();
    components.reserve(8);
    transform = addComponent<CTransform>();
}


bool GameObject::removeComponent(std::shared_ptr<Component> ptr){
    for(auto iter = components.begin(); iter != components.end(); iter++){
        if(*iter == ptr){
            components.erase(iter);
            ptr.reset();
            return true;
        }
    }
    return false;
}


shared_ptr<CSprite> GameObject::addComponentSprite(){
    CSprite* s = new CSprite(this);
    sprite = shared_ptr<CSprite>(s);
    return sprite;
}


shared_ptr<CSpriteTexture> GameObject::addComponentSpriteTexture(){
    CSpriteTexture* s = new CSpriteTexture(this);
    auto t = shared_ptr<CSpriteTexture>(s);
    sprite = t;
    return t;
}


void GameObject::update(float dt){
    for(auto& c : components){
        c->update(dt);
    }
}

void GameObject::draw(){
    if(sprite == nullptr)
        sprite = getComponent<CSprite>();
    sprite->draw();
}
