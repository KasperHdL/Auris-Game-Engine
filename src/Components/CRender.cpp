#include "CRender.hpp"
#include "../GameObject.hpp"
#include "CTransform.hpp"

void CRender::draw(){
    shader->setVector("color", color);
    SimpleRenderEngine::instance->draw(mesh, gameObject->transform->globalTransform(), shader);
}
