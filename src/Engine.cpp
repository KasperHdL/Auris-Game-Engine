#include "Engine.hpp"
#include "DebugDraw.hpp"

#include "GameObjects/Player.hpp"
#include "Input.hpp"
#include "Keys.hpp"

using namespace SRE;
using namespace glm;

DebugDraw debugDraw;

void Engine::startup(){

    renderSystem.startup(16);

    world = new b2World(toB2(glm::vec2(0,0)));

    world->SetDebugDraw(&debugDraw);
    debugDraw.SetFlags(b2Draw::e_shapeBit);

    auto sre = SimpleRenderEngine::instance;
    sre->getCamera()->setWindowCoordinates();
    sre->setLight(0, Light(LightType::Point,{-1, 1,1},{0,0,0},{5,0,0},5,20)); 
    sre->setLight(1, Light(LightType::Point,{0, 1, -2}, {0,0,0}, {3,3,3},5, 20));
    sre->setLight(2, Light(LightType::Directional,{0,0,0},{1,1,1},{1,1,1},0,20)); 
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
	Input input;
	Keys keys;

	//EXAMPLES START
	keys.setKey("w", SDL_SCANCODE_W);
	keys.setKey("s", SDL_SCANCODE_S);
	keys.setKey("a", SDL_SCANCODE_A);
	keys.setKey("d", SDL_SCANCODE_D);
	//EXAMPLES END

	//Initialize MemoryLeakDetector
	memLeakDet = MemoryLeakDetector();

	//EXAMPLES START
   
    cout << "Total phys. mem.:\t\t\t" << memLeakDet.getTotalPhysMem() << endl;
    cout << "Phys. mem. used:\t\t\t" <<  memLeakDet.getPhysMemUsed() << endl;
    cout << "Total virt. mem.:\t\t\t" << memLeakDet.getTotalVirtMem() << endl;
    cout << "Virt. mem. used:\t\t\t" << memLeakDet.getVirtMemUsed() << endl;

    cout << "Current virt. memory used by me:\t" << memLeakDet.getVirtMemUsedByMe() << endl;
    cout << "Current phys. memory used by me:\t" << memLeakDet.getPhysMemUsedByMe() << endl;
	cout << "Total CPU:\t\t\t\t" << memLeakDet.getCurrentTotalCPUValue() << endl;
	cout << "Total CPU used by this process:\t\t" << memLeakDet.getCurrentProcessCPUValue() << endl;
	//EXAMPLES END

    while (quit == 0){
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTimeSec = clamp(((NOW - LAST) / (float)SDL_GetPerformanceFrequency() ),0.0f,1.0f);
		
        sre->clearScreen(vec4(0.3f,0.3f,0.3f,1));
		input.update();
        HandleSDLEvents();
		if (input.keyDown(keys.getKey("quit"))) {
			quit = 1;
		}
		//EXAMPLES START
		if (input.keyDown(keys.getKey("up"))||input.keyDown(keys.getKey("w"))) {
			cout << "GOING UP" << endl;
		}
		if (input.keyDown(keys.getKey("down"))||input.keyDown(keys.getKey("s"))) {
			cout << "GOING DOWN" << endl;
		}
		if (input.keyDown(keys.getKey("left"))||input.keyDown(keys.getKey("a"))) {
			cout << "GOING LEFT" << endl;
		}
		if (input.keyDown(keys.getKey("right"))||input.keyDown(keys.getKey("d"))) {
			cout << "GOING RIGHT" << endl;
		}
		//EXAMPLES END

        //UPDATE
        for(auto& el: gameObjects)
            el->update(deltaTimeSec);
 
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
