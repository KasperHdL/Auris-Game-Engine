#pragma once

#include "Auris/Entities/PhysicsEntity.hpp"
#include "Box2D/Box2D.h"

#include <iostream>
namespace Auris{
class CollisionHandler : public b2ContactListener{

private:
    void BeginContact(b2Contact* contact){
        // Get PhysicsEntities that are colliding
        PhysicsEntity* colliderA = (PhysicsEntity*) contact->GetFixtureA()->GetBody()->GetUserData();
        PhysicsEntity* colliderB = (PhysicsEntity*) contact->GetFixtureB()->GetBody()->GetUserData();

        contact->SetEnabled(true);

        // Call their respective collision functions if they both have collision events enabled
        if (colliderA != nullptr & colliderB != nullptr) {
            colliderA->OnCollisionEnter(colliderB);
            colliderB->OnCollisionEnter(colliderA);
        }
    }

    void EndContact(b2Contact* contact) {
        // Get PhysicsEntities that are colliding
        PhysicsEntity* colliderA = (PhysicsEntity*) contact->GetFixtureA()->GetBody()->GetUserData();
        PhysicsEntity* colliderB = (PhysicsEntity*) contact->GetFixtureB()->GetBody()->GetUserData();

        contact->SetEnabled(false);

        // Call their respective collision functions if they both have collision events enabled
        if (colliderA != nullptr & colliderB != nullptr) {
            colliderA->OnCollisionExit(colliderB);
            colliderB->OnCollisionExit(colliderA);
        }
    }
};
}
