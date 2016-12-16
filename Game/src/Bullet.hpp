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

    Bullet(vec2 position = vec2(0, 0)) : PhysicsEntity(){
        type = "Bullet";

        //sprite = Auris::RenderSystem::getSprite(this);

        b2PolygonShape shape;
        shape.SetAsBox(0.5f * Constants::PIXELS_TO_METERS, 0.1f * Constants::PIXELS_TO_METERS);

        body = Auris::Utilities::BodyStandard::getDynamicBody(&shape, position);

        // Physics properties
        setCollisionEvents(true);
        setFixedRotation(true);
        setBullet(true);
        setGravity(0);
    }

    void update(float dt) {
        applyForce(vec2(1,0) * movementSpeed, true);
    }

    //void

};
