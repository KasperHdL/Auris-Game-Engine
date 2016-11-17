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

#include "../SpriteSheet.hpp"


using namespace std;
class Player : public GameObject{
    public:

    Player(b2World* world, vec2 position = vec2(0,0)):GameObject(){
        name = "Player";


        SpriteSheet* ss = new SpriteSheet(SRE::Texture::createFromFile("data/MarioPacked.png",false),"data/MarioPacked.json");
        //cout << sprite->color.x << endl;
        sprite = ss->getSprite("mario_10",this);
        //Material mat1;
        //mat1.mesh = Mesh::createCube();
        //mat1.texture = SRE::Texture::createFromFile("data/cartman.png",false);
        //mat1.color = vec4(1,1,1,1);
        //define sprite
        //sprite = RenderSystem::getSprite(this);
        //s->mesh = Mesh::createCube();
        //s->texture = SRE::Texture::createFromFile("data/cartman.png",false);
        //s->color = vec4(1,1,1,1);
        //mat1.set(sprite);
        sprite->scale = vec2(1.0f, 1.0f);
        //sprite = s;

        auto a = RenderSystem::getAnim(this, 4.0f);
        a->setSheet(ss);
        //a->setTexture(SRE::Texture::createFromFile("data/cartman.png", false));
        //a->setTexture(SRE::Texture::createFromFile("data/fugl.png", false));
        //a->setTexture(SRE::Texture::createFromFile("data/hammer.png", false));
        //a->setTexture(SRE::Texture::createFromFile("data/rainbow.png", false));
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
