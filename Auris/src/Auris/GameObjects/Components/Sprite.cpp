#include "Auris/GameObjects/Components/Sprite.hpp"
#include "Auris/GameObjects/GameObject.hpp"
#include "Auris/Systems/RenderSystem.hpp"
#include "Auris/Utilities/Shader.hpp"

using namespace Auris;

Sprite::~Sprite(){
}

void Sprite::draw(){
    SRE::Shader* shader = Auris::Shader::getLitSprite();
    shader->set("color",color);
    shader->set("tex",texture);
    SimpleRenderEngine::instance->draw(mesh, gameObject->globalTransform(),shader);
}
