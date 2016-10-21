#include "Engine.hpp"


using namespace SRE;
using namespace glm;
#include <iostream>

#include "Components/CTransform.hpp"
#include "Components/CSprite.hpp"
#include "Components/CDynamicBody.hpp"
#include "Components/CFixedBody.hpp"
#include "DebugDraw.hpp"

DebugDraw draw;

void Engine::startup(){

    scene = new Scene();

    {
        shared_ptr<GameObject> g = make_shared<GameObject>(GameObject());
        g->transform->localPosition = vec2(30,30);
        g->transform->localScale = vec2(1.0f, 1.0f);
        
        auto r = g->addComponentSpriteTexture();
        r->mesh = Mesh::createCube();
        r->color = vec4(1,0,0,1);
        r->texture = Texture::createFromFile("data/cartman.png",false);

        auto b = g->addComponent<CDynamicBody>();

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

        b->init(scene->world, bodyDef, fixtureDef);

        scene->add(g);
    } 

    {
        shared_ptr<GameObject> g = make_shared<GameObject>(GameObject());
        g->transform->localPosition = vec2(10,10);
        g->transform->localScale = vec2(10.0f, 1.0f);
        g->transform->localRotation = -0.5f;
        
        auto r = g->addComponentSprite();
        r->mesh = Mesh::createCube();
        r->color = vec4(1,0,0,1);

        auto b = g->addComponent<CFixedBody>();

        b2PolygonShape shape;
        shape.SetAsBox(10.0f,1.0f, b2Vec2(10.0f,10.0f), -0.5f);
        b2BodyDef bodyDef;

        b->init(scene->world, bodyDef, &shape);

        scene->add(g);
 
    
    }

    scene->world->SetDebugDraw(&draw);
    draw.SetFlags(b2Draw::e_shapeBit);
}

void Engine::shutdown(){
    delete scene;
    scene = nullptr;
}


void Engine::run(){
    // delta time from http://gamedev.stackexchange.com/a/110831
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    quit = 0;
    float deltaTimeSec = 0;
    auto sre = SimpleRenderEngine::instance;

    sre->getCamera()->setWindowCoordinates();
 
    sre->setLight(0, Light(LightType::Point,{-1, 1,1},{0,0,0},{5,0,0},5,20)); 
    sre->setLight(1, Light(LightType::Point,{0, 1, -2}, {0,0,0}, {3,3,3},5, 20));
    sre->setLight(2, Light(LightType::Directional,{0,0,0},{1,1,1},{1,1,1},0,20)); 

   
    while (quit == 0){
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTimeSec = clamp(((NOW - LAST) / (float)SDL_GetPerformanceFrequency() ),0.0f,1.0f);

        sre->clearScreen(vec4(0.3f,0.3f,0.3f,1));

        HandleSDLEvents();
        
        scene->update(deltaTimeSec);
//        scene->draw();

        scene->world->DrawDebugData();

       
        sre->swapWindow();
        SDL_Delay(16);
    }

}


void Engine::HandleSDLEvents(){
    // message processing loop
    SDL_Event event;
    /* Poll for events */
    while( SDL_PollEvent( &event ) ){
        
        switch( event.type ){
            case SDL_QUIT:
                quit = 1;
                break;
            default:
                break;
        }
        
    }


}
