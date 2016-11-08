#include "Engine.hpp"
#include "DebugDraw.hpp"

#include <glm/gtc/random.hpp>
#include "GameObjects/Player.hpp"
#include "Input.hpp";
#include "Keys.hpp";

using namespace SRE;
using namespace glm;

DebugDraw debugDraw;


void Engine::startup(){

    renderSystem.startup(16);

    particleSystem.startup(20000, 1, SRE::Texture::createFromFile("data/cartman.png",false));

    world = new b2World(toB2(glm::vec2(0,0)));

    world->SetDebugDraw(&debugDraw);
    debugDraw.SetFlags(b2Draw::e_shapeBit);

    auto sre = SimpleRenderEngine::instance;
    sre->getCamera()->setWindowCoordinates();
    sre->setLight(0, Light(LightType::Point,{-1, 1,1},{0,0,0},{5,0,0},5,20)); 
    sre->setLight(1, Light(LightType::Point,{0, 1, -2}, {0,0,0}, {3,3,3},5, 20));
    sre->setLight(2, Light(LightType::Directional,{0,0,0},{1,1,1},{1,1,1},0,20)); 

    gameObjects.push_back(make_shared<Player>(world, vec2(15,15)));
   // gameObjects.push_back(make_shared<Player>(world, vec2(10,15)));
   // gameObjects.push_back(make_shared<Player>(world, vec2(15,10)));
   // gameObjects.push_back(make_shared<Player>(world, vec2(10,10)));

	//Run init on all gameobjects
	for(auto& el: gameObjects)
            el->Init();

}

void Engine::shutdown(){
    renderSystem.shutdown();

    delete world;
    world = nullptr;

    gameObjects.clear();
}


void Engine::run(){
    // delta time from http://gamedev.stackexchange.com/a/110831
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    quit = 0;
    float deltaTimeSec = 0;
    auto sre = SimpleRenderEngine::instance;

    while (quit == 0){
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTimeSec = clamp(((NOW - LAST) / (float)SDL_GetPerformanceFrequency() ),0.0f,1.0f);
		
        sre->clearScreen(vec4(0.3f,0.3f,0.3f,1));

		for(auto& el: gameObjects)
           el->Update(deltaTimeSec);

		Input::update();
        HandleSDLEvents();
        //Run update on all gameobjects!!

 

        for(int i = 0; i < 100; i++)
        particleSystem.emit(
                vec3(width/2, height / 2, 0), //position
                vec3(glm::circularRand<float>(600.0f), 0), //velocity
                vec4(glm::sphericalRand<float>(1.0f), glm::linearRand<float>(0,1)), //color
                glm::linearRand<float>(0,1), //size
                vec4(0), //end color
                0 //end size
                );
        particleSystem.update(deltaTimeSec);
        particleSystem.draw();


        world->Step(deltaTimeSec, VELOCITY_ITERATIONS, POSITION_ITERATIONS);         
       
        //DRAW
        renderSystem.update(deltaTimeSec);

        world->DrawDebugData(); 
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
