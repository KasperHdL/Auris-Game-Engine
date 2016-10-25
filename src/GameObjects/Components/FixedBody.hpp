#pragma once

#include "Component.hpp"
#include "Box2D/Box2D.h"

class FixedBody : public Component{
    public:
        
        b2Body* body;

        FixedBody(GameObject* gameObject):Component(gameObject){
        };

        void init(b2World* world, b2BodyDef bodyDef, b2Shape* shape){
           body = world->CreateBody(&bodyDef); 
           body->CreateFixture(shape, 1.0f);
        }


};
