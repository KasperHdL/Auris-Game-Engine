#include "Auris/GameObjects/Components/Sprite.hpp"
#include "Auris/GameObjects/GameObject.hpp"
#include "Auris/Systems/RenderSystem.hpp"


Sprite::~Sprite(){
    delete texture;
    delete mesh;
}

void Sprite::draw(){
    Shader* shader = Shader::getUnlitSprite();
    shader->set("color",color);
    shader->set("tex",texture);
    SimpleRenderEngine::instance->draw(mesh, gameObject->globalTransform(),shader);
}
