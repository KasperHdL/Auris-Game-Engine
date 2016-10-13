#include <SRE/Shader.hpp>
#include "Box2DTest.hpp"
#include "SDL.h"
#include "glm/gtc/matrix_transform.hpp"
#include "SRE/Debug.hpp"
#include "SRE/Text.hpp"
#include "SRE/Texture.hpp"
#include <iostream>
#include <glm/gtx/closest_point.hpp>
#include <time.h>       /* time */
#include "DebugDraw.hpp"
#include "glm/glm.hpp"


using namespace glm;
using namespace SRE;

b2World* Box2DTest::world;
DebugDraw draw;


b2Body* bird;
bool hasLeftTheGround = false;
bool reset = false;

b2Vec2 camOffset = b2Vec2(40.0f,20.0f);

Box2DTest::Box2DTest(int width, int height) {
    this->width = width;
    this->height = height;
    
    //TODO: Initialize your world from here!
    Box2DTest::world = new b2World(b2Vec2(0,-9.89f));
 
    
    //TODO: Implement make  Box2DTest extend b2ContactListener, to allow for collision handling!
    world->SetContactListener(this);
    
	{
 	b2BodyDef edgebd;
    b2Body* fixed = world->CreateBody(&edgebd);

    b2EdgeShape edge;

    //floor
    edge.Set(camOffset + b2Vec2(-20.0f, 0.0f), camOffset + b2Vec2(20.0f, 0.0f));
    fixed->CreateFixture(&edge, 0.0f);

    //ceiling
    edge.Set(camOffset + b2Vec2(-20.0f,10.0f), camOffset + b2Vec2(20.0f, 10.0f));
    fixed->CreateFixture(&edge, 0.0f);

    //pillars
    b2PolygonShape pillar;
    pillar.SetAsBox(1.0f, 2.0f, camOffset + b2Vec2(-10.0f, 2.0f), 0.0f);
    fixed->CreateFixture(&pillar, 1.0f);

    pillar.SetAsBox(1.0f, 1.5f, camOffset + b2Vec2(-10.0f, 8.5f), 0.0f);
    fixed->CreateFixture(&pillar, 1.0f);

    pillar.SetAsBox(1.0f, 2.5f, camOffset + b2Vec2(0.0f, 2.5f), 0.0f);
    fixed->CreateFixture(&pillar, 1.0f);

    pillar.SetAsBox(1.0f, 1.0f, camOffset + b2Vec2(0.0f, 9.0f), 0.0f);
    fixed->CreateFixture(&pillar, 1.0f);


    pillar.SetAsBox(1.0f, 4.0f, camOffset + b2Vec2(7.0f, 4.0f), 0.0f);
    fixed->CreateFixture(&pillar, 1.0f);


    pillar.SetAsBox(1.0f, 2.0f, camOffset + b2Vec2(18.0f, 8.0f), 0.0f);
    fixed->CreateFixture(&pillar, 1.0f);

    pillar.SetAsBox(1.0f, 2.0f, camOffset + b2Vec2(18.0f, 2.0f), 0.0f);
    fixed->CreateFixture(&pillar, 1.0f);


    b2CircleShape shape;
    shape.m_radius = 0.5f;

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(camOffset.x + -19.0f, camOffset.y + 1.0f);
    bd.fixedRotation = true;

    b2FixtureDef fd;
    fd.shape = &shape;
    fd.friction = 1.0f;
    fd.density = 20.0f;

    bird = world->CreateBody(&bd);
    bird->CreateFixture(&fd);
	}
    
    
    world->SetDebugDraw(&draw);
    draw.SetFlags(b2Draw::e_shapeBit);
}

Box2DTest::~Box2DTest() {
    delete Box2DTest::world;
    Box2DTest::world = nullptr;
}

void Box2DTest::startGameLoop() {
    // delta time from http://gamedev.stackexchange.com/a/110831
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    quit = 0;
    float deltaTimeSec = 0;
    auto sre = SimpleRenderEngine::instance;

    sre->getCamera()->setWindowCoordinates();
    
    while (quit == 0){
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTimeSec = clamp(((NOW - LAST) / (float)SDL_GetPerformanceFrequency() ),0.0f,1.0f);

        sre->clearScreen(vec4(0.3f,0.3f,0.3f,1));

        HandleSDLEvents();
        
        //Update physics
        world->Step(1/60.f, 10, 10);
         if(hasLeftTheGround)
            {
                b2Vec2 v = bird->GetLinearVelocity();
                v.x = 3;
                bird->SetLinearVelocity(v);
            
            }
            if(reset){
                bird->SetTransform(camOffset + b2Vec2(-19.0f,1.0f),0.0f);
                bird->SetLinearVelocity(b2Vec2(0,0));
                reset = false;
            }

        //Debug Draw your physics
        world->DrawDebugData();

        //draw.DrawCircle(b2Vec2(5.0f,5.0f), 1.0f, b2Color(1.0f,1.0f,1.0f));

        sre->swapWindow();
        SDL_Delay(16);
    }
}

//TODO: implement BeginContact from the contactListener, to handle collisions
//void BeginContact(b2Contact* contact)

void Box2DTest::HandleSDLEvents()
{
    // message processing loop
    SDL_Event event;
    /* Poll for events */
    while( SDL_PollEvent( &event ) ){
        
        switch( event.type ){
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_SPACE)
                {
                    float impulse = bird->GetMass() * 300;
                bird->ApplyForceToCenter(b2Vec2(0,impulse), true);
                hasLeftTheGround = true;
                }
                break;
                /* SDL_QUIT event (window close) */
            case SDL_QUIT:
                quit = 1;
                break;
                
            default:
                break;
        }
        
    }
}

void Box2DTest::BeginContact(b2Contact* contact){
    if(hasLeftTheGround){
        hasLeftTheGround = false;
        reset = true;
    }

}

