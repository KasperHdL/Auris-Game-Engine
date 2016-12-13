#include "Auris/GameObjects/Components/Sprite.hpp"
#include "Auris/GameObjects/GameObject.hpp"
#include "Auris/Systems/RenderSystem.hpp"
#include "Auris/Utilities/Shader.hpp"

using namespace Auris;

Sprite::~Sprite(){
}

void Sprite::draw(){
    shader->set("color",color);
    if(normalMap != nullptr)
        shader->set("normalMap", normalMap, 1);
    shader->set("tex",texture, 0);
    SimpleRenderEngine::instance->draw(mesh, gameObject->globalTransform(),shader);
}
