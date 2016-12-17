#pragma once
#include "Auris/Engine.hpp"
#include "Auris/Entities/PhysicsEntity.hpp"

using namespace std;
using namespace Auris;

class Player;

class Bullet : public PhysicsEntity {
public:
    int damage = 10;

    vec2 direction;
    float speed = 10;

    Player* player;
    Sprite* sprite;

    Bullet(vec2 position = vec2(0, 0), float rotation = 0, vec2 direction = vec2(0,0), Player* player = nullptr) : PhysicsEntity(){
        type = "Bullet";
        name = "Bullet";

        sprite = RenderSystem::getSprite(this, AssetManager::getTexture("bullet.png"));

        b2PolygonShape shape;
        shape.SetAsBox(0.5f * Constants::PIXELS_TO_METERS, 0.1f * Constants::PIXELS_TO_METERS);

        body = Auris::Utilities::BodyStandard::getDynamicBody(&shape, position);

        this->direction = direction;
        this->player = player;
        setRotation(rotation);

        // Physics properties
        setCollisionEvents(true);
        setFixedRotation(true);
        setBullet(true);
        transform->setScale(vec2(0.5, 0.5));
        setGravity(0);
    }

    ~Bullet() {
        RenderSystem::deleteSprite(sprite);
    }

    void update(float dt) {
        applyForce(direction*speed, true);
    }

    void OnCollisionEnter(PhysicsEntity* other) {
        if (other->type == "Wall")
            Game::instance->destroyEntity(this);
    }
};
