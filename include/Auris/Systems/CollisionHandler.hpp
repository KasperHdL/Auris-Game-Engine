#pragma once

#include "Auris/GameObjects/GameObject.hpp"
#include "Box2D/Box2D.h"

namespace Auris{
class CollisionHandler : public b2ContactListener{

private:
    void BeginContact(b2Contact* contact){
        // Get gameobjects that collide
        GameObject* colliderA = (GameObject*) contact->GetFixtureA()->GetBody()->GetUserData();
        GameObject* colliderB = (GameObject*) contact->GetFixtureB()->GetBody()->GetUserData();

        contact->SetEnabled(true);

        // Call their respective collision functions if they both have collision events enabled
        if (colliderA != nullptr & colliderB != nullptr) {
            colliderA->OnCollisionEnter(colliderB);
            colliderB->OnCollisionEnter(colliderA);
        }
    }

    void EndContact(b2Contact* contact) {
        // Get gameobjects that collide
        GameObject* colliderA = (GameObject*) contact->GetFixtureA()->GetBody()->GetUserData();
        GameObject* colliderB = (GameObject*) contact->GetFixtureB()->GetBody()->GetUserData();

        contact->SetEnabled(false);

        // Call their respective collision functions if they both have collision events enabled
        if (colliderA != nullptr & colliderB != nullptr) {
            colliderA->OnCollisionExit(colliderB);
            colliderB->OnCollisionExit(colliderA);
        }
    }
};
}
