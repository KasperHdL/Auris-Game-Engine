#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>
#include <vector>
#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/Mesh.hpp>
#include <SRE/Shader.hpp>


using namespace glm;
using namespace std;

class Transform;
class Sprite;

class GameObject{
public:

    shared_ptr<Transform> transform;
    shared_ptr<Sprite> sprite;

    GameObject(vec2 position = vec2(0,0), float rotation = 0, vec2 scale = vec2(1,1));
        
    ~GameObject(){}

    virtual void update(float dt){};

};
