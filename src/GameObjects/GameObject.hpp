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
class Animation;

class GameObject{
public:

    GameObject* parent = nullptr;

    b2Body* body;
	Sprite* sprite;
	shared_ptr<Animation> anim;

    GameObject(){};
        
~GameObject();

    glm::mat4 localTransform();
    glm::mat4 globalTransform();

	//ALL THE SCRIPT FUNCTIONS!!!
	virtual void Init() {} // Called upon initialization

	virtual void Start() {} // Called just before first update

	virtual void Update(float deltaTime) {} // Called every frame

	virtual void OnDestruction() {} // Called when object is destroyed

	virtual void OnCollisionEnter() {} // Called upon collision with another game object

	virtual void OnCollisionStay() {} // Called while colliding with another game object

	virtual void OnCollisionExit() {} // Called when exiting collision with another game object

};
