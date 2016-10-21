#include "Engine.hpp"


using namespace SRE;
using namespace glm;
#include <iostream>

#include "Components/CTransform.hpp"
#include "Components/CSprite.hpp"
#include "Components/CDynamicBody.hpp"


void Engine::startup(){

    scene = new Scene();

    shared_ptr<GameObject> g = make_shared<GameObject>(GameObject());
    g->transform->localPosition = vec2(width/2, height/2);
    
    auto r = g->addComponentSpriteTexture();
    r->mesh = Mesh::createCube();
    r->color = vec4(1,0,0,1);
    r->texture = Texture::createFromFile("data/cartman.png",false);

    auto b = g->addComponent<CDynamicBody>();

    b2CircleShape shape;
    shape.m_radius = 0.5f;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 0.0f);
    bodyDef.fixedRotation = true;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.friction = 1.0f;
    fixtureDef.density = 20.0f;

    b->init(scene->world, bodyDef, fixtureDef);

    scene->add(g);
}

void Engine::shutdown(){

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
        scene->draw();

       
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
