#pragma once

#include "Auris/Entity.hpp"
#include "Box2D/Box2D.h"
#include "Auris/Utilities/Convert.hpp"
#include "glm/glm.hpp"

namespace Auris{
    using namespace glm;
    class PhysicsEntity : public Entity{
    public:
        b2Body* body;

        virtual void updateTransform() {
            transform->position = vec3(Convert::toGlm(body->GetPosition()),transform->position.z);
            transform->rotation = body->GetAngle();
        } // Called every frame

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

        void setBullet(bool flag){
            body->SetBullet(flag);
        }
     
        // Getters 
        vec2 getLinearVelocity() { 
            return Convert::toGlm(body->GetLinearVelocity()); 
        }

        bool isBullet() {
            return body->IsBullet();
        }

        virtual void OnCollisionEnter(PhysicsEntity* collider) {} //! Called upon collision with another PhysicsEntity
     
        virtual void OnCollisionStay(PhysicsEntity* collider) {} //! Called while colliding with another PhysicsEntity
     
        virtual void OnCollisionExit(PhysicsEntity* collider) {} //! Called when exiting collision with another PhysicsEntity


    };
}
