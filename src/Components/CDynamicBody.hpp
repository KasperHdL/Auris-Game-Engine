#pragma once

#include "Component.hpp"
#include "Box2D/Box2D.h"
#include <memory>

class CDynamicBody : public Component{
public:

    b2Body* body;
    void init(b2World* world, b2BodyDef bodyDef, b2FixtureDef fixtureDef){
       body = world->CreateBody(&bodyDef); 
       body->CreateFixture(&fixtureDef);
    }

protected:
 
    CDynamicBody(GameObject* gameObject):Component(gameObject){}

    friend class GameObject;
};
