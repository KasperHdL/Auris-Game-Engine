#pragma once

#include "Box2D/Box2D.h"
#include "glm/glm.hpp"
#include "Auris/Engine.hpp"

namespace Auris{
namespace Utilities{

//! A BodyStandard namespace
    /*! Controls two body standards and makes them from box2D
     * Dynamic body and static body
    */
namespace BodyStandard{


//! A getDynamicBody method, taking 1-5 arguments.
    /*!
     * Creates a dynamic body from box2D and returns it
     * \param shape a b2Shape pointer. The shape of the body.
     * \param position a vec2 value. The position of the body (default is in origin (vec2(0))).
     * \param friction a float value. The friction of the body (default is 1.0).
     * \param density a float value. The density of the body (default is 20.0).
     * \param restitution a float value. The restitution of the body (default is 0.0).
     * \return b2Body pointer. A pointer to the dynamic body created.
    */
    static b2Body* getDynamicBody(b2Shape* shape, glm::vec2 position = glm::vec2(0), float friction = 1.0f, float density = 20.0f, float restitution = 0.0f){
        
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position.x, position.y);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = shape;
        fixtureDef.friction = friction;
        fixtureDef.density = density;
        fixtureDef.restitution = restitution;

        b2Body* body;
        body = Engine::world->CreateBody(&bodyDef);
        body->CreateFixture(&fixtureDef);

        return body;

    }

    //! A getStaticBody method, taking 1-5 arguments.
        /*!
         * Creates a dynamic body from box2D and returns it
         * \param shape a b2Shape pointer. The shape of the body.
         * \param position a vec2 value. The position of the body (default is in origin (vec2(0))).
         * \param friction a float value. The friction of the body (default is 1.0).
         * \param density a float value. The density of the body (default is 20.0).
         * \param restitution a float value. The restitution of the body (default is 0.0).
         * \return b2Body pointer. A pointer to the static body created.
        */
    static b2Body* getStaticBody(b2Shape* shape, glm::vec2 position = glm::vec2(0), float friction = 1.0f, float density = 20.0f, float restitution = 0.0f){
        b2BodyDef bodyDef; 
        bodyDef.type = b2_staticBody; 
        bodyDef.position.Set(position.x, position.y); 

        b2FixtureDef fixtureDef; 
        fixtureDef.shape = shape; 
        fixtureDef.friction = friction; 
        fixtureDef.density = density;
        fixtureDef.restitution = restitution;
 
        b2Body* body;
        body = Engine::world->CreateBody(&bodyDef);
        body->CreateFixture(&fixtureDef);  

        return body;
    }


}
}
}
