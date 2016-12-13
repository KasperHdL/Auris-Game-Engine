#include "Auris/Entities/Nuggets/Sprite.hpp"
#include "Auris/Entity.hpp"
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
    SimpleRenderEngine::instance->draw(mesh, entity->transform->getGlobal(), shader);
}
