#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Auris/Utilities/Convert.hpp"

#include <memory>
#include <vector>
#include <SRE/SimpleRenderEngine.hpp>

#include "Box2D/Box2D.h"

using namespace glm;
using namespace std;

namespace Auris{
class Sprite;

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


    // Box2D encapsulation

    // Vectors
    vec2 up = vec2(0, 1);
    vec2 down = vec2(0, -1);
    vec2 left = vec2(-1, 0);
    vec2 right = vec2(1, 0);

    // Setters
    void setCollisionEvents(bool flag){
        if (flag)
            body->SetUserData(this);
        else
            body->SetUserData(nullptr);
    }

    void setGravity(float gravityScale) {
        body->SetGravityScale(gravityScale);
    }

    void setFixedRotation(bool flag) {
        body->SetFixedRotation(flag);
    }

    void setActive (bool flag) {
        body->SetActive(flag);
    }

    void applyForce(vec2 force, bool impulse = false, bool awake = true) {
        if (impulse)
            body->ApplyLinearImpulseToCenter(Convert::toB2(force), awake);
        else
            body->ApplyForceToCenter(Convert::toB2(force), awake);
    }

    void applyForce(vec2 force, vec2 point, bool impulse = false,  bool awake = true){
        if (impulse)
            body->ApplyLinearImpulse(Convert::toB2(force), Convert::toB2(point), awake);
        else
            body->ApplyForce(Convert::toB2(force), Convert::toB2(point), awake);
    }

    // Getters
    vec2 getLinearVelocity() {
        return Convert::toGlm(body->GetLinearVelocity());
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
}
