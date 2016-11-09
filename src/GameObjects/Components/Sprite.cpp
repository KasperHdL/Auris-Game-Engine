#include "Sprite.hpp"
#include "../GameObject.hpp"

void Sprite::draw(){
material->set();
    SimpleRenderEngine::instance->draw(mesh, gameObject->globalTransform(), material->shader);
}
