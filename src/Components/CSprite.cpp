#include "CSprite.hpp"
#include "../GameObject.hpp"
#include "CTransform.hpp"

void CSprite::draw(){
    Shader* shader = Shader::getUnlitSprite();
    shader->setVector("color", color);
    SimpleRenderEngine::instance->draw(mesh, gameObject->transform->globalTransform(), shader);
}

void CSpriteTexture::draw(){
    Shader* shader = Shader::getUnlitSprite();
    shader->setVector("color", color);
    shader->setTexture("tex", texture);
    SimpleRenderEngine::instance->draw(mesh, gameObject->transform->globalTransform(), shader);
}
