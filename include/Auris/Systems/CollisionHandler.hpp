#pragma once

#include "Auris/Entities/PhysicsEntity.hpp"
#include "Box2D/Box2D.h"

#include <iostream>
namespace Auris{

//! The CollisionHandler class that extend the b2ContactListener from box2D
    /*! Handles all collision of the engine
    */
class CollisionHandler : public b2ContactListener{

private:

    //! A BeginContact overload method, taking 1 argument.
        /*!
         * If there is a contact between two bodies, sent their information to one another
         * \param contact a b2Contact pointer, that is the contact happening.
         * \overload b2ContactListener::BeginContact(b2Contact* contact)
        */
    void BeginContact(b2Contact* contact){
        // Get PhysicsEntities that are colliding
        PhysicsEntity* colliderA = (PhysicsEntity*) contact->GetFixtureA()->GetBody()->GetUserData();
        PhysicsEntity* colliderB = (PhysicsEntity*) contact->GetFixtureB()->GetBody()->GetUserData();

        contact->SetEnabled(true);

        // Call their respective collision functions if they both have collision events enabled
        if (colliderA != nullptr && colliderB != nullptr) {
            colliderA->OnCollisionEnter(colliderB);
            colliderB->OnCollisionEnter(colliderA);
        }
    }

    //! An EndContact overload method, taking 1 argument.
        /*!
         * If contact is ending between two bodies, sent their information to one another
         * \param contact a b2Contact pointer, that is the contact endind.
         * \overload b2ContactListener::EndContact(b2Contact* contact)
        */
    void EndContact(b2Contact* contact) {
        // Get PhysicsEntities that are colliding
        PhysicsEntity* colliderA = (PhysicsEntity*) contact->GetFixtureA()->GetBody()->GetUserData();
        PhysicsEntity* colliderB = (PhysicsEntity*) contact->GetFixtureB()->GetBody()->GetUserData();

        contact->SetEnabled(false);

        // Call their respective collision functions if they both have collision events enabled
        if (colliderA != nullptr && colliderB != nullptr) {
            colliderA->OnCollisionExit(colliderB);
            colliderB->OnCollisionExit(colliderA);
        }
    }
};
}
