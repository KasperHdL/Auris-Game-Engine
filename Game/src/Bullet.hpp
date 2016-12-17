#pragma once
#include "Auris/Engine.hpp"
#include "Auris/Entities/PhysicsEntity.hpp"

using namespace std;
using namespace Auris;

class Player;

class Bullet : public PhysicsEntity {
public:
    int damage = 10;

    vec2 direction = vec2(0,0);
    float speed = 10;

    Player* player = nullptr;
    Sprite* sprite;

    Bullet(vec2 position = vec2(0, 0)) : PhysicsEntity(){
        type = "Bullet";

        sprite = RenderSystem::getSprite(this, AssetManager::getTexture("bullet.png"));

        b2PolygonShape shape;
        shape.SetAsBox(0.5f * Constants::PIXELS_TO_METERS, 0.1f * Constants::PIXELS_TO_METERS);

        body = Auris::Utilities::BodyStandard::getDynamicBody(&shape, position);

        // Physics properties
        setCollisionEvents(true);
        setFixedRotation(true);
        setBullet(true);
        setGravity(0);
    }

    ~Bullet() {
        RenderSystem::deleteSprite(sprite);
    }

    void update(float dt) {
        applyForce(direction*speed, true);
    }

    void OnCollisionEnter(PhysicsEntity* other) {

    }
};
