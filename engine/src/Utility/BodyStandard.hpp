#pragma once

#include "Box2D/Box2D.h"
#include "glm/glm.hpp"
#include "../Auris.hpp"

namespace Utility{

using namespace glm;

namespace BodyStandard{

    static b2Body* getDynamicBody(b2Shape* shape, vec2 position = vec2(0), float friction = 1.0f, float density = 20.0f){
        
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position.x, position.y);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = shape;
        fixtureDef.friction = friction;
        fixtureDef.density = density;

        b2Body* body;
        body = Auris::world->CreateBody(&bodyDef);
        body->CreateFixture(&fixtureDef);

        return body;

    }

    static b2Body* getStaticBody(b2Shape* shape, vec2 position = vec2(0), float friction = 1.0f, float density = 20.0f){
        b2BodyDef bodyDef; 
        bodyDef.type = b2_staticBody; 
        bodyDef.position.Set(position.x, position.y); 

        b2FixtureDef fixtureDef; 
        fixtureDef.shape = shape; 
        fixtureDef.friction = friction; 
        fixtureDef.density = density; 
 
        b2Body* body;
        body = Auris::world->CreateBody(&bodyDef); 
        body->CreateFixture(&fixtureDef);  

        return body;
    }


};
}
