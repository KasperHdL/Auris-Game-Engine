#include "Engine.hpp"


using namespace SRE;
using namespace glm;
#include <iostream>

#include "Components/CTransform.hpp"
void Engine::startup(){

    GameObject* g = new GameObject();
    shared_ptr<CTransform> t = g->addComponent<CTransform>();
    t->localPosition.x = 10;
    std::cout << t->localPosition.x << std::endl;

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
    sre->getCamera()->setPerspectiveProjection(60,640,480,0.1,100);
 
    sre->getCamera()->lookAt({10,10,10}, {0,0,0}, {0,1,0});
    sre->setLight(0, Light(LightType::Point,{-1, 1,1},{0,0,0},{5,0,0},5,20)); 
    sre->setLight(1, Light(LightType::Point,{0, 1, -2}, {0,0,0}, {3,3,3},5, 20));
    sre->setLight(2, Light(LightType::Directional,{0,0,0},{1,1,1},{1,1,1},0,20)); 

   
    while (quit == 0){
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTimeSec = clamp(((NOW - LAST) / (float)SDL_GetPerformanceFrequency() ),0.0f,1.0f);

        sre->clearScreen(vec4(0.3f,0.3f,0.3f,1));

        HandleSDLEvents();

       
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
