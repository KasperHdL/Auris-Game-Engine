#include "GameObject.hpp"

using namespace SRE;

GameObject::GameObject(Mesh *mesh, Shader *shader)
:mesh(mesh), shader(shader)
{
    color = {1,1,1,1};

    position = {0,0,0};
    rotation = {0,0,0};
    scale = {1,1,1};

    parent = nullptr;
}

void GameObject::draw() {
    shader->setVector("color", color);
    SimpleRenderEngine::instance->draw(mesh,globalTransform(),shader);
}

glm::mat4 GameObject::localTransform() {
    glm::mat4 rx = glm::eulerAngleX((rotation.x));
    glm::mat4 ry = glm::eulerAngleY((rotation.y));
    glm::mat4 rz = glm::eulerAngleZ((rotation.z));

    glm::mat4 t = glm::translate(glm::mat4(1), position);
    glm::mat4 s = glm::scale(glm::mat4(1), scale);

    return t * (rz * ry * rx) * s;
}

glm::mat4 GameObject::globalTransform() {
    if(parent == nullptr)
        return localTransform();

    return parent->globalTransform() * localTransform();
}

