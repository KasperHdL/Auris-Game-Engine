#pragma once
#include "Auris/Engine.hpp"
#include "Auris/Entities/PhysicsEntity.hpp"

using namespace std;
using namespace Auris;

class Bullet : public PhysicsEntity {
public:
    int damage = 10;
    float movementSpeed = 10;

    Sprite* sprite;

    Bullet(vec2 position) : PhysicsEntity(){
        name = "Bullet";

        sprite = Auris::RenderSystem::getSprite(this);

        b2PolygonShape shape;
        shape.SetAsBox(0.5f * Constants::PIXELS_TO_METERS, 0.1f * Constants::PIXELS_TO_METERS);

        body = Auris::Utilities::BodyStandard::getDynamicBody(&shape, position);

        // Physics properties
        setCollisionEvents(true);
        setFixedRotation(true);
        setGravity(0);
    }

    void Update(float dt) {
        applyForce(vec2(1,0) * movementSpeed);
    }

};