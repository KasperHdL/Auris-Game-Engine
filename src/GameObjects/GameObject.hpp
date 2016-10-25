#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>
#include <vector>
#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/Mesh.hpp>
#include <SRE/Shader.hpp>
#include "Box2D/Box2D.h"


using namespace glm;
using namespace std;

class Sprite;

class GameObject{
public:

    GameObject* parent = nullptr;

    b2Body* body;
    shared_ptr<Sprite> sprite;

    GameObject(){};
        
    ~GameObject(){}

    virtual void update(float dt){};

    glm::mat4 localTransform();
    glm::mat4 globalTransform();

};
