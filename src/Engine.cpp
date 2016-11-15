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
    sre->setLight(2, Light(LightType::Directional,{0,0,0},{1,1,1},{1,1,1},0));

    gameObjects.push_back(make_shared<Player>(world));
    gameObjects.push_back(make_shared<Player>(world));

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

	//EXAMPLES END

	//Initialize MemoryLeakDetector
	memLeakDet = MemoryLeakDetector();

    //DEBUG INFORMATION TODO should be ignored on release build
 
    keys.setKey("debug", SDL_SCANCODE_F2);
    keys.setKey("pause", SDL_SCANCODE_F3);
    keys.setKey("stepOne", SDL_SCANCODE_F4);
    keys.setKey("playOnHold", SDL_SCANCODE_F5);


    keys.setKey("arrow_up", SDL_SCANCODE_UP);
    keys.setKey("arrow_down", SDL_SCANCODE_DOWN);
    keys.setKey("arrow_left", SDL_SCANCODE_LEFT);
    keys.setKey("arrow_right", SDL_SCANCODE_RIGHT);
    

   
    int arrIndex = 0;
    const int arrSize = 600;
    float arr_deltaTime[arrSize] = {};
    float max_deltaTime = 0;

    
    float arr_virtMem[arrSize] = {};
    float max_virtMem = 0;

    float arr_physMem[arrSize] = {};
    float max_physMem = 0;

    int max_renderSprites = 0;

    bool toggle_goInspector = false;
    bool toggle_cameraControls = false;

    while (quit == 0){
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTimeSec = clamp(((NOW - LAST) / (float)SDL_GetPerformanceFrequency() ),0.0f,1.0f);
		
        sre->clearScreen(vec4(0,0,0,1));

		input.update();
        HandleSDLEvents();

		if (input.keyDown(keys.getKey("quit"))) {
			quit = 1;
		}

        if(input.keyDown(keys.getKey("debug"))){
            debug = !debug;

            if(debug == false){
                ImGui_SRE_NewFrame(window);
                ImGui::Render();
            }
        }

        if(input.keyDown(keys.getKey("pause"))){
            pause = !pause;
        }

        bool runOneStep = false;
        if(input.keyDown(keys.getKey("stepOne")) || input.keyHeld(keys.getKey("playOnHold"))){
            runOneStep = true;
            pause = true;
        }

        if(debug){
            
            ImGui_SRE_NewFrame(window);

            ImGui::Checkbox("Debug(F2)", &debug);
            ImGui::SameLine();
            ImGui::Checkbox("Pause(F3)", &pause);
            if(ImGui::Button("Step One Frame(F4)")){
                runOneStep = true;
                pause = true;
            }
            ImGui::SameLine();
            ImGui::Text("Play on Hold(F5)");
//            ImGui::Checkbox("Toggle Camera Controls(Arrow Keys)",&toggle_cameraControls);

            ImGui::Checkbox("Toggle GO Inspector",&toggle_goInspector);
            ImGui::Separator();

            arr_deltaTime[arrIndex] = deltaTimeSec;
            arr_physMem[arrIndex] = memLeakDet.getPhysMemUsedByMe();
            arr_virtMem[arrIndex] = memLeakDet.getVirtMemUsedByMe();

            if(deltaTimeSec > max_deltaTime)
                max_deltaTime = deltaTimeSec;

            if(renderSystem.spritePool.count > max_renderSprites)
                max_renderSprites = renderSystem.spritePool.count;

            ImGui::PlotLines("Physical Memory", arr_physMem, arrSize);
            ImGui::Text("Physical Memory: %f / %f", arr_physMem[arrIndex], memLeakDet.getTotalPhysMem());
            ImGui::PlotLines("Dt", arr_virtMem, arrSize);
            ImGui::Text("Virtual Memory: %f / %f", arr_virtMem[arrIndex], memLeakDet.getTotalVirtMem());

            ImGui::Separator();
            ImGui::PlotLines("Dt", arr_deltaTime, arrSize);
            ImGui::Text("Current Dt: %f - Max dt: %f",deltaTimeSec, max_deltaTime);

            ImGui::Separator();
            ImGui::Text("Num GameObjects %zu", gameObjects.size());
            ImGui::Text("Num of Sprites Allocated %d - Max %d", renderSystem.spritePool.count, max_renderSprites);

            ImGui::Separator();

            if(toggle_goInspector){
                ImGui::Begin("GameObject Inspector");
                if(ImGui::TreeNode("GameObjects")){
                    int i = 0;
                    for(auto& el: gameObjects){
                        string name = el->name;
                        if(name == "") name = &"GO " [ i];

                        ImGui::PushID(&el);
                        if(ImGui::TreeNode(el->name.c_str())){
                            vec2 pos = toGlm(el->body->GetPosition());
                            ImGui::Text("Position (%f, %f)", pos.x, pos.y);

                            ImGui::Text("Rotation (%f)", el->body->GetAngle());

                            vec2 vel = toGlm(el->body->GetLinearVelocity());
                            ImGui::Text("Velocity (%f, %f)", vel.x, vel.y);
                            
                            ImGui::Text("Angular Velocity (%f)", el->body->GetAngularVelocity());

                            ImGui::TreePop();
                        }
                        ImGui::PopID();
                        i++;
                    }
                    ImGui::TreePop();
                }
                ImGui::End();
            }



            arrIndex++;
            if(arrIndex >= arrSize)
                arrIndex = 0;

            ImGui::Render();
        }

        //UPDATE
        if(!pause || runOneStep){
            for(auto& el: gameObjects)
                el->update(deltaTimeSec);

            for(int i = 0; i < 100; i++)
            particleSystem.emit(
                    vec3(width/2, height / 2, 0), //position
                    vec3(glm::circularRand<float>(800.0f), 0), //velocity
                    vec4(glm::sphericalRand<float>(1.0f), 0), //color
                    glm::linearRand<float>(0,1), //size
                    vec4(0,0,0,1), //end color
                    1 //end size
                    );
            particleSystem.update(deltaTimeSec);

            world->Step(deltaTimeSec, VELOCITY_ITERATIONS, POSITION_ITERATIONS);         
           
        }
        //DRAW
        particleSystem.draw();
        renderSystem.update(deltaTimeSec);

        world->DrawDebugData();
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
