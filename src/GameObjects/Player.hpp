#pragma once

#include "GameObject.hpp"
#include "Box2D/Box2D.h"
#include "Components/Sprite.hpp"

#include "../RenderSystem.hpp"
#include "../Constants.hpp"


class Player : public GameObject{
    public:

    Player(b2World* world, vec2 position = vec2(0,0)):GameObject(){

        auto s = RenderSystem::getSpriteTexture(this);
        s->mesh = Mesh::createCube();
        s->color = vec4(1,1,1,1);
        s->texture = SRE::Texture::createFromFile("data/cartman.png",false);
        s->scale = vec2(s->texture->getWidth(), s->texture->getHeight());
        sprite = s;

        b2CircleShape shape;
        shape.m_radius = (s->scale.x * Constants::PIXELS_TO_METERS);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.friction = 1.0f;
        fixtureDef.density = 20.0f;

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position.x, position.y);

        body = world->CreateBody(&bodyDef); 
        body->CreateFixture(&fixtureDef);

    }

         
};
