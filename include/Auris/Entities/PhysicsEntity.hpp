#pragma once

#include "Auris/Entity.hpp"
#include "Box2D/Box2D.h"
#include "Auris/Utilities/Convert.hpp"
#include "glm/glm.hpp"

namespace Auris{
    using namespace glm;

//! The PhysicsEntity class that extend the Entity class
    /*! Used to control physic objects.
    */
    class PhysicsEntity : public Entity{
    public:
        b2Body* body; /*!< A b2Body pointer: body. Reference to the physics body. */

        //! The overloaded method updateTransform.
            /*! Updates the enitities transform according to the physics body.
             * Should not be used by the game programmer.
             * Called every frame.
             * \overload Entity::updateTransform()
            */
        virtual void updateTransform() {
            transform->position = vec3(Convert::toGlm(body->GetPosition()),transform->position.z);
            transform->rotation = body->GetAngle();
        }

        //! The method setCollisionEvents.
            /*! set the collision event on or off in box2D
             * \param flag a bool value, that controls on or off (true = on).
            */
        void setCollisionEvents(bool flag){ 
            if (flag) 
                body->SetUserData(this); 
            else 
                body->SetUserData(nullptr); 
        } 
        //! The method setGravity.
            /*! set the scale of gravity in box2D
             * \param gravityScale a float value, that is the scale of the gravity.
            */
        void setGravity(float gravityScale) { 
            body->SetGravityScale(gravityScale); 
        } 
     
        //! The method setFixedRotation.
            /*! set the fixed rotation of the object in box2D
             * \param flag a bool value, that controls  the fixed rotation.
            */
        void setFixedRotation(bool flag) { 
            body->SetFixedRotation(flag); 
        } 
     
        //! The method setActive.
            /*! sets if the box2D body should be active
             * \param flag a bool value, that controls if the body is active.
            */
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
