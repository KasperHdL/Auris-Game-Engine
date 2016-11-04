#include "Sprite.hpp"
#include "../GameObject.hpp"

void Sprite::draw(){
    Shader* shader = Shader::getUnlitSprite();
    shader->setVector("color", color);
	shader->setTexture("tex", texture);
    SimpleRenderEngine::instance->draw(mesh, gameObject->globalTransform(), shader);
}

//void SpriteTexture::draw(){
//    Shader* shader = Shader::getUnlitSprite();
//    shader->setVector("color", color);
//    shader->setTexture("tex", texture);
//    SimpleRenderEngine::instance->draw(mesh, gameObject->globalTransform(), shader);
//}


