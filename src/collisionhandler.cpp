#include "collisionhandler.h"

CollisionHandler::CollisionHandler()
{

}

void CollisionHandler::BeginContact(b2Contact* contact) {
    b2Fixture* colliderA = contact->GetFixtureA();
    b2Fixture* colliderB = contact->GetFixtureB();
}

void EndContact(b2Contact* contact) {
    b2Fixture* colliderA = contact->GetFixtureA();
    b2Fixture* colliderB = contact->GetFixtureB();
}


