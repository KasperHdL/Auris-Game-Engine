#pragma once

#include "Auris/Entity.hpp"
#include "Box2D/Box2D.h"
#include "Auris/Utilities/Convert.hpp"
#include "glm/glm.hpp"
#include "Auris/Engine.hpp"

namespace Auris{
    using namespace glm;

//! The PhysicsEntity class that extend the Entity class
    /*! Used to control physic objects.
    */
    class PhysicsEntity : public Entity{

    private:
        b2Vec2 lastPosition;
        float lastAngle;
    public:
        b2Body* body; /*!< A b2Body pointer: body. Reference to the physics body. */


        //! The overloaded method updateTransform.
            /*! Updates the enitities transform according to the physics body.
             * Should not be used by the game programmer.
             * Called every frame.
             * \overload Entity::updateTransform()
            */
        virtual void updateTransform() {
            b2Vec2 p = body->GetPosition();
            if(lastPosition != p){
                transform->setPosition(Convert::toGlm(p));
                lastPosition = p;
            }
            float a = body->GetAngle();
            if(lastAngle != a){
                transform->setRotation(a);
                lastAngle = a;
            }
        }

        ~PhysicsEntity();

        //! The method setCollisionEvents, taking 1 argument.
            /*! set the collision event on or off in box2D
             * \param flag a bool value, that controls on or off (true = on).
            */
        void setCollisionEvents(bool flag){ 
            if (flag) 
                body->SetUserData(this); 
            else 
                body->SetUserData(nullptr); 
        } 
        //! The method setGravity, taking 1 argument.
            /*! set the scale of gravity in box2D
             * \param gravityScale a float value, that is the scale of the gravity.
            */
        void setGravity(float gravityScale) { 
            body->SetGravityScale(gravityScale); 
        } 
     
        //! The method setFixedRotation, taking 1 argument.
            /*! set the fixed rotation of the object in box2D
             * \param flag a bool value, that controls  the fixed rotation.
            */
        void setFixedRotation(bool flag) { 
            body->SetFixedRotation(flag); 
        }

        //! The method setRotation, taking 1 argument.
            /*! set the rotation of the object in box2D
             * \param rotation a float value, that controls the rotation.
            */
        void setRotation(float rotation) {
            body->SetTransform(body->GetPosition(), rotation);
            transform->setRotation(rotation);
        }
     
        //! The method setAwake, taking 1 argument.
            /*! sets if the box2D body should be active
             * \param flag a bool value, that controls if the body is active.
            */
        void setAwake (bool flag) { 
            body->SetAwake(flag);
        } 
     
        //! The applyForce method, taking 1-3 arguments.
            /*! Applies force to the physics entity center via box2D body
             * \param force a vec2 value, that is the force that should be apllied.
             * \param impule a bool value, that is if the force is an impulse or not (default is false).
             * \param awake a bool value, that is if the box2D body can receive physics updates (default is true).
            */
        void applyForce(vec2 force, bool impulse = false, bool awake = true) { 
            if (impulse) 
                body->ApplyLinearImpulseToCenter(Convert::toB2(force), awake); 
            else 
                body->ApplyForceToCenter(Convert::toB2(force), awake); 
        } 
     
        //! The applyForce method, taking 2-4 arguments.
            /*! Applies force to the physics entity on a specific point via box2D body
             * \param force a vec2 value, that is the force that should be apllied.
             * \param point a vec2 value, that is the point where the force should be applied.
             * \param impule a bool value, that is if the force is an impulse or not (default is false).
             * \param awake a bool value, that is if the box2D body can receive physics updates (default is true).
             * \overload applyForce(vec2 force, bool impulse = false, bool awake = true)
            */
        void applyForce(vec2 force, vec2 point, bool impulse = false,  bool awake = true){ 
            if (impulse) 
                body->ApplyLinearImpulse(Convert::toB2(force), Convert::toB2(point), awake); 
            else 
                body->ApplyForce(Convert::toB2(force), Convert::toB2(point), awake); 
        } 

        //! The setBullet method, taking 1 argument.
            /*! Set the body to bullet physics, meaning that if the entity is moving fast it will still not clip through stuff
             * \param awake a bool value, that is if the box2D body is a bullet.
            */
        void setBullet(bool flag){
            body->SetBullet(flag);
        }
     
        //! The getLinearVelocity method.
            /*! Gets the linear velocity of the box2D body associated with the physics entity.
             * \return vec2, that is the velocity
            */
        vec2 getLinearVelocity() { 
            return Convert::toGlm(body->GetLinearVelocity()); 
        }

        //! The isBullet method.
            /*! Gets if the body is using bullet physics, so if it potentially goes so fast that it needs to not clip through objects
             * \return bool, that is if the body is bullet
            */
        bool isBullet() {
            return body->IsBullet();
        }

        //! The scriptable function onCollisionEnter.
            /*!
             * Used by the game programmer to add on collision enter functionality to the physics entity.
             * Called upon collision with another PhysicsEntity
             * \param collider a PhysicsEntity pointer, that is the physics entity colliding with
            */
        virtual void OnCollisionEnter(PhysicsEntity* collider) {}
     
        //! The scriptable function onCollisionExit.
            /*!
             * Used by the game programmer to add on collision exit functionality to the physics entity.
             * Called when exiting collision with another PhysicsEntity
             * \param collider a PhysicsEntity pointer, that is the physics entity colliding with
            */
        virtual void OnCollisionExit(PhysicsEntity* collider) {} //! Called when exiting collision with another PhysicsEntity

        //! The scriptable function inspectorImGui.
            /*!
             * Used by the game programmer to add inspector GUI functionality to the entity.
             * Is called every frame, when the inspector gui is open
             * The game programmer can call PhysicsEntity::inspectorImGui to get Transform, Position, Scale and Rotation inspection
            */
        virtual void inspectorImGui(){
            if(ImGui::TreeNode("Physics Transform")){
                glm::vec3 pos = transform->getPositionVec3();
                float rotation = transform->getRotation();
                glm::vec2 scale = transform->getScale();

                glm::vec2 vel = Convert::toGlm(body->GetLinearVelocity());
                float rvel = body->GetAngularVelocity();
                float mass = body->GetMass();
            
                ImGui::DragFloat3("Position", &pos.x,0.1f);
                ImGui::DragFloat("Rotation", &rotation,0.1f);
                ImGui::DragFloat2("Scale", &scale.x, 0.1f);

                ImGui::DragFloat2("Velocity", &vel.x);
                ImGui::DragFloat("Angular Velocity", &rvel);
                ImGui::DragFloat("Mass", &mass);

                if(pos != transform->getPositionVec3() || rotation != transform->getRotation()){
                    transform->setPosition(pos);
                    transform->setRotation(rotation);
                    body->SetTransform(Convert::toB2(pos), rotation);
                    setAwake(true);
                }

                if(scale != transform->getScale())
                    transform->setScale(scale);

                if(Convert::toB2(vel) != body->GetLinearVelocity())
                    body->SetLinearVelocity(Convert::toB2(vel));

                if(rvel != body->GetAngularVelocity())
                    body->SetAngularVelocity(rvel);

                ImGui::TreePop();
            } 
        }

    };
}
