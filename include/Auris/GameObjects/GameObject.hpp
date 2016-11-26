#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>
#include <vector>
#include <SRE/SimpleRenderEngine.hpp>
#include "Box2D/Box2D.h"


using namespace glm;
using namespace std;

class Sprite;
class Animation;

class GameObject{
public:

    string name = "";
    GameObject* parent = nullptr;

    b2Body* body;

	Sprite* sprite;

    GameObject();
    ~GameObject();
       

    glm::mat4 localTransform();
    glm::mat4 globalTransform();

    void enableCollisionEvents(){
        body->SetUserData(this);
    }

    // Scriptable functions

	virtual void Init() {} // Called upon initialization

	virtual void Start() {} // Called just before first update

	virtual void Update(float deltaTime) {} // Called every frame

	virtual void OnDestruction() {} // Called when object is destroyed

    virtual void OnCollisionEnter(GameObject* collider) {} // Called upon collision with another game object

    virtual void OnCollisionStay(GameObject* collider) {} // Called while colliding with another game object

    virtual void OnCollisionExit(GameObject* collider) {} // Called when exiting collision with another game object

};
