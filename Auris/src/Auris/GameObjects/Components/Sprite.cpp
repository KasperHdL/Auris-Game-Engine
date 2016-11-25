#include "Auris/GameObjects/Components/Sprite.hpp"
#include "Auris/GameObjects/GameObject.hpp"

void Sprite::draw(){
    Shader* shader = Shader::getUnlitSprite();
    shader->set("color",color);
    shader->set("tex",texture);
    SimpleRenderEngine::instance->draw(mesh, gameObject->globalTransform(),shader);
}
