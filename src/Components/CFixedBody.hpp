#pragma once

#include "Component.hpp"
#include "Box2D/Box2D.h"

class CFixedBody : Component{
    
    b2Body* body;

    CFixedBody(GameObject* gameObject):Component(gameObject){
    };

    void init(b2World* world, b2BodyDef bodyDef, b2FixtureDef fd){
       body = world->CreateBody(&bodyDef); 
       body->CreateFixture(&fd);
    }


};
