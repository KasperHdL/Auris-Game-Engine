#include "Sprite.hpp"
#include "../GameObject.hpp"

void Sprite::draw(){
    Shader* shader = Shader::getUnlitSprite();
    shader->set("color",color);
    shader->set("tex",texture);
    SimpleRenderEngine::instance->draw(mesh, gameObject->globalTransform(),shader);
}
