#pragma once

#include "GameObject.hpp"
#include "Box2D/Box2D.h"
#include "Components/Sprite.hpp"
#include "src/Animation.hpp"

#include "../RenderSystem.hpp"
#include "../Constants.hpp"
#include <iostream>
#include "src/Input.hpp"
#include "src/Keys.hpp"
#include "src/Material.hpp"


using namespace std;
class Player : public GameObject{
    public:

    Player(b2World* world, vec2 position = vec2(0,0)):GameObject(){

        Material mat1;
        mat1.mesh = Mesh::createCube();
        mat1.texture = SRE::Texture::createFromFile("data/cartman.png",false);
        mat1.color = vec4(1,1,1,1);
        //define sprite
        auto s = RenderSystem::getSprite(this);
        //s->mesh = Mesh::createCube();
        //s->texture = SRE::Texture::createFromFile("data/cartman.png",false);
        //s->color = vec4(1,1,1,1);
        mat1.set(s);
        s->scale = vec2(s->texture->getWidth(), s->texture->getHeight());
        sprite = s;

		auto a = RenderSystem::getAnim(this, 4.0f);
		a->setTexture(SRE::Texture::createFromFile("data/cartman.png", false));
		a->setTexture(SRE::Texture::createFromFile("data/fugl.png", false));
		a->setTexture(SRE::Texture::createFromFile("data/hammer.png", false));
		a->setTexture(SRE::Texture::createFromFile("data/rainbow.png", false));
		anim = a;
		
        //body & fixture definitions and create & assign body
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position.x, position.y);

        b2CircleShape shape;
        shape.m_radius = (s->scale.x * Constants::PIXELS_TO_METERS);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.friction = 1.0f;
        fixtureDef.density = 20.0f;

        body = world->CreateBody(&bodyDef); 
        body->CreateFixture(&fixtureDef);
    }

	float force;
	Keys keys;
	void Init() {
		force = 10000.0f;
	}

    void Update(float dt){
		//sprite->texture = anim->getSprite();
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
