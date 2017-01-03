#pragma once
#include "Auris/Auris.hpp"

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

    Bullet(vec2 position = vec2(0, 0), float rotation = 0, vec2 direction = vec2(0,0), Player* player = nullptr, int groupIndex = 0) : PhysicsEntity(){
        type = "Bullet";
        name = "Bullet";

        sprite = RenderSystem::getSprite(this, AssetManager::getTexture("bullet.png"));

        b2PolygonShape shape;
        shape.SetAsBox(0.5f * Constants::PIXELS_TO_METERS, 0.1f * Constants::PIXELS_TO_METERS);

        b2Filter filter;
        filter.groupIndex = groupIndex;

        body = Auris::Utilities::BodyStandard::getDynamicBody(&shape, false, 1.0f, 20.0f, 0.0f, &filter);

        this->direction = direction;
        this->player = player;
        setRotation(rotation);

        // Physics properties
        setCollisionEvents(true);
        setPosition(position);
        setFixedRotation(true);
        setBullet(true);
        transform->setScale(vec2(0.5f, 0.5f));
        setGravity(0);
    }

    ~Bullet() {
        RenderSystem::deleteSprite(sprite);
    }

    void update(float dt) {
        applyForce(direction*speed, true);
    }

    void OnCollisionEnter(PhysicsEntity* other) {
        //cout<<other->type<<endl;
        if (other->type == "Wall"||other->type=="Floor"||other->type == "Player"||other->type=="Roof")
            Game::instance->destroyEntity(this);
    }
};
