#pragma once

#include "GameObject.hpp"
#include "Box2D/Box2D.h"
#include "Components/Transform.hpp"
#include "Components/Sprite.hpp"
#include "Components/DynamicBody.hpp"


class Player : public GameObject{
    public:
    shared_ptr<DynamicBody> body;

    Player(b2World* world):GameObject(){
        transform->localScale = vec2(100,100);
        shared_ptr<SpriteTexture> s = make_shared<SpriteTexture>(this);
        s->mesh = Mesh::createCube();
        s->color = vec4(1,1,0,1);
        s->texture = SRE::Texture::createFromFile("data/cartman.png",false);
        sprite = s;

        shared_ptr<DynamicBody> b = make_shared<DynamicBody>(this);

        b2CircleShape shape;
        shape.m_radius = 1.0f;

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(10.0f,30.0f);
        bodyDef.fixedRotation = true;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.friction = 1.0f;
        fixtureDef.density = 20.0f;

        b->init(world, bodyDef, fixtureDef);
    }

         
    void update(float dt){
        sprite->draw();

    }

};
