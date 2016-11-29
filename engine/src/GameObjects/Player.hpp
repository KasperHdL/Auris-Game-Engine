#pragma once

#include "GameObject.hpp"
#include "Components/Sprite.hpp"
#include "Components/Animation.hpp"

#include "../Systems/RenderSystem.hpp"
#include "../Constants.hpp"
#include <iostream>
#include "../Systems/Input.hpp"
#include "Components/Material.hpp"
#include <iostream>

#include "Components/SpriteSheet.hpp"


using namespace std;
class Player : public GameObject{
    public:

    SpriteSheet* ss;

    Player(b2World* world, vec2 position = vec2(0,0)):GameObject(){
        name = "Player";

        ss = new SpriteSheet(SRE::Texture::createFromFile("data/MarioPacked.png",false),"data/MarioPacked.json");

        sprite = ss->getSprite("mario_10",this);

        sprite->scale = vec2(1.0f, 1.0f);

        auto a = RenderSystem::getAnim(this, 4.0f);
        a->setSheet(ss);

		anim = a;
		
        //body & fixture definitions and create & assign body
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position.x, position.y);

        b2CircleShape shape;
        shape.m_radius = (19 * Constants::PIXELS_TO_METERS);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.friction = 1.0f;
        fixtureDef.density = 20.0f;

        body = world->CreateBody(&bodyDef); 
        body->CreateFixture(&fixtureDef);
    }

    ~Player() {
        delete ss;
    }

	float force;
	Keys keys;

	void Init() {
		force = 10000.0f;
	}

    void Update(float dt){
        anim->setSprite(sprite);
		if (Input::keyHeld(keys.getKey("up"))) {
			body->ApplyForceToCenter(b2Vec2(0, force), true);
		}
		if (Input::keyHeld(keys.getKey("down"))) {
			body->ApplyForceToCenter(b2Vec2(0, -force), true);
		}
		if (Input::keyHeld(keys.getKey("left"))) {
			body->ApplyForceToCenter(b2Vec2(-force, 0), true);
		}
		if (Input::keyHeld(keys.getKey("right"))) {
			body->ApplyForceToCenter(b2Vec2(force, 0), true);
		}
    }
};
