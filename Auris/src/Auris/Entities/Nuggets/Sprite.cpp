#include "Auris/Entities/Nuggets/Sprite.hpp"
#include "Auris/Entity.hpp"
#include "Auris/Systems/RenderSystem.hpp"
#include "Auris/Utilities/Shader.hpp"

using namespace Auris;

Sprite::~Sprite(){
}

void Sprite::draw(){
    material.shader->set("color",material.color);

    if(material.normalMap != nullptr)
        material.shader->set("normalMap", material.normalMap, 1);

    material.shader->set("tex",material.texture, 0);
    SimpleRenderEngine::instance->draw(mesh, entity->transform->getGlobal(offset), material.shader);
}
