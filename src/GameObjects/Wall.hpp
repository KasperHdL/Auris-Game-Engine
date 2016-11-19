#pragma once

#include "GameObject.hpp"
#include "Components/SpriteSheet.hpp"
#include "../Constants.hpp"

using namespace Constants;

class Wall : public GameObject{
public:
    Wall(b2World* world, vec2 position = vec2(0,0)):GameObject() {
        name = "Wall";

        SpriteSheet* ss = new SpriteSheet(SRE::Texture::createFromFile("data/MarioPacked.png",false),"data/MarioPacked.json");
        sprite = ss->getSprite("brick",this);

        sprite->scale = vec2(1.0f, 1.0f);

        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(position.x, position.y);

        b2PolygonShape shape;
        shape.SetAsBox(30.0f * PIXELS_TO_METERS, 30.0f * PIXELS_TO_METERS);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.friction = 1.0f;
        fixtureDef.density = 20.0f;

        body = world->CreateBody(&bodyDef);
        body->CreateFixture(&fixtureDef);

        enableCollisionEvents();
    }

    void OnCollisionEnter(GameObject* other) {
        cout << name << " hit " << other->name << endl;
    }

    void OnCollisionExit(GameObject* other) {
        cout << name << " is longer colliding with " << other->name << endl;
    }
};
