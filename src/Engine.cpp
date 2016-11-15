#include "Engine.hpp"
#include "DebugDraw.hpp"

#include <glm/gtc/random.hpp>
#include "GameObjects/Player.hpp"
#include "Input.hpp"
#include "Keys.hpp"

#include "SRE/imgui_sre.hpp"

using namespace SRE;
using namespace glm;

DebugDraw debugDraw;


void Engine::startup(SDL_Window* window){
    ImGui_SRE_Init(window);

    renderSystem.startup(16);

    particleSystem.startup(10000, 1, SRE::Texture::createFromFile("data/cartman.png",false));

    world = new b2World(toB2(glm::vec2(0,0)));

    world->SetDebugDraw(&debugDraw);
    debugDraw.SetFlags(b2Draw::e_shapeBit);

    auto sre = SimpleRenderEngine::instance;
    sre->getCamera()->setWindowCoordinates();
    sre->setLight(0, Light(LightType::Point,{-1, 1,1},{0,0,0},{5,0,0},5));
    sre->setLight(1, Light(LightType::Point,{0, 1, -2}, {0,0,0}, {3,3,3},5));
    sre->setLight(2, Light(LightType::Directional,{0,0,0},{1,1,1},{1,1,1},0));

    gameObjects.push_back(make_shared<Player>(world, vec2(15,15)));
    gameObjects.push_back(make_shared<Player>(world, vec2(10,15)));
    gameObjects.push_back(make_shared<Player>(world, vec2(15,10)));
    gameObjects.push_back(make_shared<Player>(world, vec2(10,10)));

}

void Engine::shutdown(){
    renderSystem.shutdown();

    delete world;
    world = nullptr;

    gameObjects.clear();
}


void Engine::run(SDL_Window* window){
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

    keys.setKey("debug", SDL_SCANCODE_F2);


	//EXAMPLES END

	//Initialize MemoryLeakDetector
	memLeakDet = MemoryLeakDetector();

	//EXAMPLES START
   
    cout << "Total phys. mem.:\t\t" << memLeakDet.totalPhysMem << endl;
    cout << "Phys. mem. used:\t\t" <<  memLeakDet.physMemUsed<< endl;
    cout << "Total virt. mem.:\t\t" << memLeakDet.totalVirtualMem << endl;
    cout << "Virt. mem. used:\t\t" << memLeakDet.virtualMemUsed << endl;

    cout << "Current virt. memory:\t\t" << memLeakDet.getCurrentVirtMemValue() << endl;
    cout << "Current phys. memory:\t\t" << memLeakDet.getCurrentPhysMemValue() << endl;
    memLeakDet.initTotalCPUFile();
	cout << "Total CPU:\t\t\t" << memLeakDet.getCurrentTotalCPUValue() << endl;
    memLeakDet.initCurrentCPUFile();
	cout << "Total CPU used by this process:\t" << memLeakDet.getCurrentProcessCPUValue() << endl;
	//EXAMPLES END

    //DEBUG INFORMATION TODO should be ignored on release build
    
    int arrIndex_deltaTime = 0;
    const int arrSize_deltaTime = 600;
    float arr_deltaTime[arrSize_deltaTime] = {};
    float max_deltaTime = 0;




    //
    while (quit == 0){
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTimeSec = clamp(((NOW - LAST) / (float)SDL_GetPerformanceFrequency() ),0.0f,1.0f);
		
        sre->clearScreen(vec4(0,0,0,1));
        ImGui_SRE_NewFrame(window);

		input.update();
        HandleSDLEvents();

		if (input.keyDown(keys.getKey("quit"))) {
			quit = 1;
		}

        if(input.keyDown(keys.getKey("debug")))
            debug = !debug;

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
 


        if(debug){

            arr_deltaTime[arrIndex_deltaTime] = deltaTimeSec;
            if(deltaTimeSec > max_deltaTime)
                max_deltaTime = deltaTimeSec;

            arrIndex_deltaTime++;
            if(arrIndex_deltaTime >= arrSize_deltaTime)
                arrIndex_deltaTime = 0;

            ImGui::Text("Physical Memory: %ll / %ll", memLeakDet.physMemUsed, memLeakDet.totalPhysMem);
            ImGui::Text("Virtual Memory: %ll / %ll", memLeakDet.virtualMemUsed, memLeakDet.totalVirtualMem);

            ImGui::Text("Num GameObjects %zu", gameObjects.size());
            
            ImGui::PlotLines(("Deltatime: " + std::to_string(deltaTimeSec)).c_str(), arr_deltaTime, arrSize_deltaTime);
            ImGui::Text("Max DeltaTime %f", max_deltaTime);



        }


        for(int i = 0; i < 10; i++)
        particleSystem.emit(
                vec3(width/2, height / 2, 0), //position
                vec3(glm::circularRand<float>(200.0f), 0), //velocity
                vec4(glm::sphericalRand<float>(1.0f), 0.1f), //color
                glm::linearRand<float>(0,1), //size
                vec4(1,1,1,0.1f), //end color
                1 //end size
                );
        particleSystem.update(deltaTimeSec);
        particleSystem.draw();


        world->Step(deltaTimeSec, VELOCITY_ITERATIONS, POSITION_ITERATIONS);         
       
        //DRAW
        renderSystem.update(deltaTimeSec);

        world->DrawDebugData();
        ImGui::Render();
        sre->swapWindow();
    }

}


void Engine::HandleSDLEvents(){
    // message processing loop
    SDL_Event event;
    /* Poll for events */
    while( SDL_PollEvent( &event ) ){
        ImGui_SRE_ProcessEvent(&event);
        
        switch( event.type ){
            case SDL_QUIT:
                quit = 1;
                break;
            default:
                break;
        }
        
    }


}
