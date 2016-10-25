#include "Sprite.hpp"
#include "../GameObject.hpp"
#include "Transform.hpp"

void Sprite::draw(){
    Shader* shader = Shader::getUnlitSprite();
    shader->setVector("color", color);
    SimpleRenderEngine::instance->draw(mesh, gameObject->transform->globalTransform(), shader);
}

void SpriteTexture::draw(){
    Shader* shader = Shader::getUnlitSprite();
    shader->setVector("color", color);
    shader->setTexture("tex", texture);
    SimpleRenderEngine::instance->draw(mesh, gameObject->transform->globalTransform(), shader);
}


