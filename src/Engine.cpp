#include "Engine.hpp"
#include "GameObjects/Player.hpp"
#include "Input.hpp";
#include "Keys.hpp";


using namespace SRE;
using namespace glm;

Player* player;

void Engine::startup(){

    world = new b2World(toB2(glm::vec2(0,-10)));
    world->SetDebugDraw(&draw);
    draw.SetFlags(b2Draw::e_shapeBit);

    player = new Player(world);

}

void Engine::shutdown(){
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

    sre->getCamera()->setWindowCoordinates();
 
    sre->setLight(0, Light(LightType::Point,{-1, 1,1},{0,0,0},{5,0,0},5,20)); 
    sre->setLight(1, Light(LightType::Point,{0, 1, -2}, {0,0,0}, {3,3,3},5, 20));
    sre->setLight(2, Light(LightType::Directional,{0,0,0},{1,1,1},{1,1,1},0,20)); 

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

        world->Step(deltaTimeSec, VELOCITY_ITERATIONS, POSITION_ITERATIONS);         
//UPDATE
        player->update(deltaTimeSec);
//DRAW
        
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
